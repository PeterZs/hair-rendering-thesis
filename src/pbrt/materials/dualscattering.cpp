
/*
    pbrt source code is Copyright(c) 1998-2016
                        Matt Pharr, Greg Humphreys, and Wenzel Jakob.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


// materials/plastic.cpp*
#include "dualscattering.h"
#include "spectrum.h"
#include "reflection.h"
#include "paramset.h"
#include "texture.h"
#include "interaction.h"
#include "materials/marschner.h"
#include "hairutil.h"
#include "hair.h"
#include "light.h"
#include "samplers/random.h"
#include "sampling.h"
#include <random>
#include "OpenVdbReader.h"
#include "materials/dualscatteringlookup.h"
#include "scene.h"
#include "materials/hairutil.h"

namespace pbrt {

    // DualscatteringMaterial Method Definitions

    void DualscatteringMaterial::ComputeScatteringFunctions(
            SurfaceInteraction *si, MemoryArena &arena, TransportMode mode,
            bool allowMultipleLobes) const {

        // Allocate a bsdf that contains the collection of BRDFs and BTDFs
        si->bsdf = ARENA_ALLOC(arena, BSDF)(*si, this->mEta);

        MarschnerBSDF* marschnerBSDF = mMarschnerMaterial->CreateMarschnerBSDF(si, arena);

        DualScatteringBSDF* dualScatteringBSDF =
                ARENA_ALLOC(arena, DualScatteringBSDF)(*si, mEta, marschnerBSDF,
                mAlphaR, mAlphaTT, mAlphaTRT, mBetaR, mBetaTT, mBetaTRT, mVoxelGridFileName);

        si->bsdf->Add(dualScatteringBSDF);
    }

    DualscatteringMaterial *CreateDualscatteringMaterial(const TextureParams &mp) {
        MarschnerMaterial* marschnerMaterial = CreateMarschnerMaterial(mp);

        // TODO: Check if dual scattering really wants to square the widths
        //        marschnerMaterial->mBr = Sqr(marschnerMaterial->mBr);
        //        marschnerMaterial->mBtt = Sqr(marschnerMaterial->mBtrt);
        //        marschnerMaterial->mBtrt = Sqr(marschnerMaterial->mBtrt);

        std::string vdbFileName = mp.FindString("vdbFileName", "voxelgrid.vdb");

        return new DualscatteringMaterial(marschnerMaterial->mEta, marschnerMaterial,
                marschnerMaterial->mAr, marschnerMaterial->mAtt, marschnerMaterial->mAtrt,
                marschnerMaterial->mBr, marschnerMaterial->mBtt, marschnerMaterial->mBtrt,
                vdbFileName);
    }

    /*******************************
     * DualScatteringBSDF
     *******************************/

    DualScatteringBSDF::DualScatteringBSDF(const SurfaceInteraction& si, Float eta,
            MarschnerBSDF* marschnerBSDF,
            Float alphaR, Float alphaTT, Float alphaTRT,
            Float betaR, Float betaTT, Float betaTRT,
            std::string voxelGridFileName)
    : BxDF(BxDFType(BSDF_GLOSSY | BSDF_REFLECTION | BSDF_TRANSMISSION)),
    mEta(eta), mDb(0.7), mDf(0.7),
    mMarschnerBSDF(marschnerBSDF),
    mPosition(si.p),
    ns(si.shading.n),
    ng(si.n),
    ss(Normalize(si.shading.dpdu)),
    ts(Cross(ns, ss)),
    mWorldToObject(*si.shape->WorldToObject),
    mObjectToWorld(*si.shape->ObjectToWorld),
    mShape(si.shape),
    mObjectBound(si.shape->ObjectBound()), mWorldBound(si.shape->WorldBound()),
    mAlphaR(alphaR), mAlphaTT(alphaTT), mAlphaTRT(alphaTRT),
    mBetaR(betaR), mBetaTT(betaTT), mBetaTRT(betaTRT),
    mVoxelGridFileName(voxelGridFileName) {
        // lookup table initialized here, so that all members
        // of this reference are initialized
        mLookup = DualScatteringLookup::Get(this);

    };

    Vector3f DualScatteringBSDF::WorldToLocal(const Vector3f &v) const {
        return Vector3f(Dot(v, ss), Dot(v, ts), Dot(v, ns));
    }

    Vector3f DualScatteringBSDF::LocalToWorld(const Vector3f &v) const {
        return Vector3f(ss.x * v.x + ts.x * v.y + ns.x * v.z,
                ss.y * v.x + ts.y * v.y + ns.y * v.z,
                ss.z * v.x + ts.z * v.y + ns.z * v.z);
    }

    /**
     *
     * @param eccentricity Eccentricity value (1 means circular)
     * @param etaPerp The index of refraction of the fiber
     * @param thetaH The longitudinal half angle
     * @return the adjusted index of refraction taking into account eccentricity
     */
    static Float EtaEccentricity(Float eccentricity, Float etaPerp, Float thetaH) {
        Float eta1 = 2.0 * (etaPerp - 1.0) * Sqr(eccentricity) - etaPerp + 2.0;
        Float eta2 = 2.0 * (etaPerp - 1.0) / Sqr(eccentricity) - etaPerp + 2.0;

        return 0.5 * ((eta1 + eta2) + cos(2.0 * thetaH)*(eta1 - eta2));
    }

    Spectrum DualScatteringBSDF::f(const Vector3f &wo, const Vector3f &wi) const {
        return Spectrum(.0);
    }

    Spectrum DualScatteringBSDF::Li(const Vector3f& wi, const Spectrum& Li, const Scene& scene, const VisibilityTester& visibilityTester) const {
        // Added this function to do occlusion checking in the material itself.
        // For Dualscattering, occlusion checking is not necessary, because we approximate the global illumination.
        return Li;
    }

    Spectrum DualScatteringBSDF::f(const Vector3f &woLocal, const Vector3f &wiLocal, const Scene &scene, const VisibilityTester& visibilityTester) const {

        const Vector3f wiWorld = LocalToWorld(wiLocal);
        const Vector3f woWorld = LocalToWorld(woLocal);

        const MarschnerAngles angles(woLocal, wiLocal, mEta, this->mMarschnerBSDF->getEccentricity());
        GlobalScatteringInformation gsi = GatherGlobalScatteringInformation(scene, visibilityTester, wiWorld, angles.thetaD);

        Spectrum forwardTransmittance = gsi.transmittance;
        Spectrum Ab = BackscatteringAttenuation(angles.thetaD);
        Spectrum deltaB = BackscatteringMean(angles.thetaD);

        Spectrum backScatterVariance = BackscatteringVariance(angles.thetaD);
        Spectrum forwardScatterVariance = gsi.variance;
        CHECK_GE(forwardScatterVariance.y(), 0.0);

        Spectrum fDirectBack = 2.0 * Ab
                * Gaussian(Sqrt(backScatterVariance), -deltaB + angles.thetaH)
                / (Pi * Sqr(cos(angles.thetaD)));

        Spectrum fScatterBack = 2.0 * Ab
                * Gaussian(Sqrt(backScatterVariance + forwardScatterVariance), -deltaB + angles.thetaH)
                / (Pi * Sqr(cos(angles.thetaD)));


        Spectrum F;

        if (gsi.isDirectIlluminated) {
            Spectrum fDirectS = mMarschnerBSDF->f(woLocal, wiLocal);
            F = fDirectS + mDb * fDirectBack;
        } else {
            Spectrum fScatterS = EvaluateForwardScatteredMarschner(angles.thetaR,
                    angles.thetaH, angles.thetaD, angles.phi, forwardScatterVariance);
            F = forwardTransmittance * mDf * (fScatterS + Pi * mDb * fScatterBack);
        }

        CHECK_GE(F.y(), 0.0);
        return F * cos(angles.thetaI);
    }

    GlobalScatteringInformation DualScatteringBSDF::GatherGlobalScatteringInformation(
            const Scene& scene, const VisibilityTester& visibilityTester,
            const Vector3f& wd, Float thetaD) const {

        GlobalScatteringInformation gsi;

        // @ref Dual-Scattering Approximation, Zinke et al (2007), section 4.1.1.

        const Ray ray(mPosition, wd);
        bool isDirectIlluminated = visibilityTester.Unoccluded(scene);

        // Interpolates a ray through a voxel grid, where each voxel contains the hair density
        // thereby returning the approximated number of hair strands intersected.

        Point3f pObject = mWorldToObject(mPosition);
        const InterpolationResult interpolationResult = this->mLookup->getVdbReader()->interpolateToInfinity(pObject, -wd);
        Float scatterCount = interpolationResult.scatterCount;

        if (isDirectIlluminated || interpolationResult.scatterCount <= 1e-5) {
            gsi.isDirectIlluminated = true;
            gsi.transmittance = 1.0;
            gsi.variance = Spectrum(.0);
        } else {
            gsi.isDirectIlluminated = false;
            gsi.transmittance = this->ForwardScatteringTransmittance(scatterCount, thetaD);
            gsi.variance = this->ForwardScatteringVariance(scatterCount, thetaD);
        }

        return gsi;
    }

    /**
     * Equation 5 in dual scattering approximation
     * @param scatterCount the amount of intersections along the shadow ray
     * @param thetaD the average orientation (thetaD) for all intersection along the shadow ray
     */
    Spectrum DualScatteringBSDF::ForwardScatteringTransmittance(Float scatterCount, Float thetaD) const {

        Spectrum s = this->mLookup->AverageForwardScatteringAttenuation(thetaD);
        return mDf * Pow(s, scatterCount);
    }

    /**
     * Equation 8
     * @param interpolationResult
     * @return
     */
    Spectrum DualScatteringBSDF::ForwardScatteringVariance(Float scatterCount, Float thetaD) const {

        return scatterCount * this->mLookup->AverageForwardScatteringBeta(thetaD);
    }

    Spectrum DualScatteringBSDF::EvaluateForwardScatteredMarschner(Float thetaR, Float thetaH, Float thetaD,
            Float phi, Spectrum forwardScatteredVariance) const {

        // TODO: remove eta perp calculation and let marschner be responsible for it
        Float etaPerp, etaPar;
        ToBravais(mEta, thetaR, etaPerp, etaPar);

        // take into account eccentricity (by again adjusting the eta)
        Float eccentricity = mMarschnerBSDF->getEccentricity();
        if (eccentricity != 1.0) {
            etaPerp = EtaEccentricity(eccentricity, etaPerp, thetaH);
        }


        Float sinThetaR = sin(thetaR);
        Float sinThetaT = sinThetaR / etaPerp;
        Float cosThetaT = SafeSqrt(1 - Sqr(sinThetaT));

        Spectrum result = (
                MG_r(2.0 * thetaH, forwardScatteredVariance) * mMarschnerBSDF->N_r(phi, etaPerp)
                + MG_tt(2.0 * thetaH, forwardScatteredVariance) * mMarschnerBSDF->N_tt(phi, etaPerp, cosThetaT)
                + MG_trt(2.0 * thetaH, forwardScatteredVariance) * mMarschnerBSDF->N_trt(phi, etaPerp, cosThetaT)
                ) / CosineSquared(thetaD);

        return result;
    }

    Spectrum DualScatteringBSDF::Sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample, Float *pdf, BxDFType * sampledType) const {

        Float theta = acos(2.0 * sample.x - 1.0);
        Float phi = 2.0 * Pi * sample.y;

        Float x = sin(theta) * cos(phi);
        Float y = sin(theta) * sin(phi);
        Float z = cos(theta);

        *wi = Vector3f(x, y, z);
        *pdf = this->Pdf(wo, *wi);

        return f(wo, *wi);
    }

    Spectrum DualScatteringBSDF::MG_r(Float theta, Spectrum forwardScatteringVariance) const {
        // WATCHOUT: do not square betaR, already squared at material creation

        return Gaussian(Spectrum(mBetaR) + forwardScatteringVariance, theta - mAlphaR);
    }

    Spectrum DualScatteringBSDF::MG_tt(Float theta, Spectrum forwardScatteringVariance) const {
        // WATCHOUT: do not square betaTT, already squared at material creation

        return Gaussian(Spectrum(mBetaTT) + forwardScatteringVariance, theta - mAlphaTT);
    }

    Spectrum DualScatteringBSDF::MG_trt(Float theta, Spectrum forwardScatteringVariance) const {
        // WATCHOUT: do not square betaTRT, already squared at material creation

        return Gaussian(Spectrum(mBetaTRT) + forwardScatteringVariance, theta - mAlphaTRT);
    }

    static Vector3f SampleFrontHemisphere(const Point2f & uv) {
        Vector3f w = UniformSampleSphere(uv);
        if (w.x < 0.0) {

            w.x *= -1.0;
        }
        return w;
    }

    /**
     * Samples in the front hemisphere for a given theta
     * @param theta Fixed theta to use
     * @param u random number between 0 and 1 for phi generation
     * @return Unit vector in the front hemisphere
     */
    static Vector3f SampleFrontHemisphere(Float theta, Float u) {
        Float phi = (-1.0 + 2.0 * u) * Pi;
        Vector3f w = FromSphericalCoords(theta, phi);

        if (w.x < 0.0) {

            w.x *= -1.0;
        }
        return w;
    }

    /**
     * Samples in the front hemisphere for a given theta
     * @param uv 2D sample to be used to sample a vector on unit sphere
     * @return Unit vector in the back hemisphere
     */
    static Vector3f SampleBackHemisphere(const Point2f & uv) {
        Vector3f w = UniformSampleSphere(uv);
        if (w.x > 0.0) {

            w.x *= -1.0;
        }
        return w;
    }

    /**
     * Samples in the back hemisphere for a given theta
     * @param theta Fixed theta to use
     * @param u random number between 0 and 1 for phi generation
     * @return Unit vector in the back hemisphere
     */
    static Vector3f SampleBackHemisphere(Float theta, Float u) {
        Float phi = (-1.0 + 2.0 * u) * Pi;
        //Float phi = (-.5 + u) * Pi;
        Vector3f w = FromSphericalCoords(theta, phi);
        if (w.x > 0.0) {

            w.x *= -1.0;
        }
        return w;
    }

    Spectrum DualScatteringBSDF::AverageForwardScatteringAttenuation(Float thetaD) const {

        Spectrum integral(.0), sum(.0);
        Float thetaR, phiR;
        MyRandomSampler sampler(0.0, 1.0);

        const int SAMPLES = 1000;
        for (int i = 0; i < SAMPLES; ++i) {

            const Vector3f woForward = SampleFrontHemisphere(Point2f(sampler.next(), sampler.next()));
            ToSphericalCoords(woForward, thetaR, phiR);

            Float thetaI = GetThetaIFromDifferenceAngle(thetaD, thetaR);
            const Vector3f wi = SampleBackHemisphere(thetaI, sampler.next());

            integral += mMarschnerBSDF->f(woForward, wi) * cos(thetaD);
        }

        return integral / static_cast<Float> (SAMPLES);
    }

    Spectrum DualScatteringBSDF::AverageBackwardScatteringAttenuation(Float thetaD) const {
        Spectrum integral(.0);
        Float thetaR, phiR;
        MyRandomSampler sampler(0.0, 1.0);

        const int SAMPLES = 1000;
        for (int i = 0; i < SAMPLES; ++i) {

            const Vector3f woBackward = SampleBackHemisphere(Point2f(sampler.next(), sampler.next()));
            ToSphericalCoords(woBackward, thetaR, phiR);

            Float thetaI = GetThetaIFromDifferenceAngle(thetaD, thetaR);
            const Vector3f wi = SampleBackHemisphere(thetaI, sampler.next());

            integral += mMarschnerBSDF->f(woBackward, wi) * cos(thetaD);
        }

        return integral / static_cast<Float> (SAMPLES);
    }

    Spectrum DualScatteringBSDF::AverageForwardScatteringAlpha(Float thetaD) const {
        Spectrum sum(.0);
        Spectrum denominator(.0);
        Float thetaR, phiR;
        MyRandomSampler sampler(0.0, 1.0);

        const int SAMPLES = 1000;
        for (int i = 0; i < SAMPLES; ++i) {

            const Vector3f woForward = SampleFrontHemisphere(Point2f(sampler.next(), sampler.next()));
            ToSphericalCoords(woForward, thetaR, phiR);

            Float thetaI = GetThetaIFromDifferenceAngle(thetaD, thetaR);
            const Vector3f wi = SampleBackHemisphere(thetaI, sampler.next());

            Spectrum fR = mMarschnerBSDF->f_r(woForward, wi);
            Spectrum fTT = mMarschnerBSDF->f_tt(woForward, wi);
            Spectrum fTRT = mMarschnerBSDF->f_trt(woForward, wi);

            sum += fR * mAlphaR + fTT * mAlphaTT + fTRT * mAlphaTRT;
            denominator += (fR + fTT + fTRT);
        }

        return sum / denominator;
    }

    Spectrum DualScatteringBSDF::AverageBackwardScatteringAlpha(Float thetaD) const {

        Spectrum sum(.0), denominator(.0);
        Float thetaR, phiR;
        MyRandomSampler sampler(0.0, 1.0);

        const int SAMPLES = 1000;
        for (int i = 0; i < SAMPLES; ++i) {

            const Vector3f woBackward = SampleBackHemisphere(Point2f(sampler.next(), sampler.next()));
            ToSphericalCoords(woBackward, thetaR, phiR);

            Float thetaI = GetThetaIFromDifferenceAngle(thetaD, thetaR);
            const Vector3f wi = SampleBackHemisphere(thetaI, sampler.next());

            Spectrum fR = mMarschnerBSDF->f_r(woBackward, wi);
            Spectrum fTT = mMarschnerBSDF->f_tt(woBackward, wi);
            Spectrum fTRT = mMarschnerBSDF->f_trt(woBackward, wi);

            sum += fR * mAlphaR + fTT * mAlphaTT + fTRT * mAlphaTRT;
            denominator += (fR + fTT + fTRT);
        }

        return sum / denominator;
    }

    Spectrum DualScatteringBSDF::AverageForwardScatteringBeta(Float thetaD) const {

        Spectrum sum(.0), denominator(.0);
        Float thetaR, phiR;
        MyRandomSampler sampler(0.0, 1.0);

        const int SAMPLES = 1000;
        for (int i = 0; i < SAMPLES; ++i) {

            const Vector3f woForward = SampleFrontHemisphere(Point2f(sampler.next(), sampler.next()));
            ToSphericalCoords(woForward, thetaR, phiR);

            Float thetaI = GetThetaIFromDifferenceAngle(thetaD, thetaR);
            const Vector3f wi = SampleBackHemisphere(thetaI, sampler.next());

            Spectrum fR = mMarschnerBSDF->f_r(woForward, wi);
            Spectrum fTT = mMarschnerBSDF->f_tt(woForward, wi);
            Spectrum fTRT = mMarschnerBSDF->f_trt(woForward, wi);

            sum += fR * mBetaR + fTT * mBetaTT + fTRT * mBetaTRT;
            denominator += (fR + fTT + fTRT);
        }

        return sum / denominator;
    }

    Spectrum DualScatteringBSDF::AverageBackwardScatteringBeta(Float thetaD) const {

        Spectrum sum(.0), denominator(.0);
        Float thetaR, phiR;
        MyRandomSampler sampler(0.0, 1.0);

        const int SAMPLES = 1000;
        for (int i = 0; i < SAMPLES; ++i) {

            const Vector3f woBackward = SampleBackHemisphere(Point2f(sampler.next(), sampler.next()));
            ToSphericalCoords(woBackward, thetaR, phiR);

            Float thetaI = GetThetaIFromDifferenceAngle(thetaD, thetaR);
            const Vector3f wi = SampleBackHemisphere(thetaI, sampler.next());

            Spectrum fR = mMarschnerBSDF->f_r(woBackward, wi);
            Spectrum fTT = mMarschnerBSDF->f_tt(woBackward, wi);
            Spectrum fTRT = mMarschnerBSDF->f_trt(woBackward, wi);

            sum += fR * mBetaR + fTT * mBetaTT + fTRT * mBetaTRT;
            denominator += (fR + fTT + fTRT);
        }

        return sum / denominator;
    }

    Spectrum DualScatteringBSDF::BackscatteringAttenuation(Float thetaD) const {
        Spectrum afSquared = Sqr(mLookup->AverageForwardScatteringAttenuation(thetaD));
        Spectrum ab = mLookup->AverageBackwardScatteringAttenuation(thetaD);

        Spectrum abPow3 = Pow3(ab);
        Spectrum oneMinusAfSquared = Spectrum(1.0) - afSquared;
        Spectrum oneMinusAfSquaredPow3 = Sqr(oneMinusAfSquared) * oneMinusAfSquared;

        Spectrum A1 = ab * afSquared / oneMinusAfSquared;
        Spectrum A3 = abPow3 * afSquared / oneMinusAfSquaredPow3;

        return A1 + A3;
    }

    //! equation 16

    Spectrum DualScatteringBSDF::BackscatteringMean(Float thetaD) const {

        // average forward and backward scattering shifts, taken from BCSDF of the hair fiber
        Spectrum alphaF = mLookup->AverageForwardScatteringAlpha(thetaD);
        Spectrum alphaB = mLookup->AverageBackwardScatteringAlpha(thetaD);

        Spectrum ab = mLookup->AverageBackwardScatteringAttenuation(thetaD);
        Spectrum af = mLookup->AverageForwardScatteringAttenuation(thetaD);

        Spectrum oneMinSquaredAf = Spectrum(1.0) - Sqr(af);
        Spectrum oneMinSquaredAfSquared = Sqr(oneMinSquaredAf);
        Spectrum oneMinSquaredAfPow3 = Pow3(oneMinSquaredAf);

        Spectrum part1 = Spectrum(1.0) - (2.0 * Sqr(ab) / oneMinSquaredAfSquared);
        Spectrum part2 = (2.0 * oneMinSquaredAfSquared + 4.0 * Sqr(af) * Sqr(ab)) / oneMinSquaredAfPow3;

        return alphaB * part1 + alphaF * part2;
    }

    //! equation 17

    Spectrum DualScatteringBSDF::BackscatteringVariance(Float thetaD) const {

        Spectrum betaF = mLookup->AverageForwardScatteringBeta(thetaD);
        Spectrum betaB = mLookup->AverageBackwardScatteringBeta(thetaD);

        Spectrum ab = mLookup->AverageBackwardScatteringAttenuation(thetaD);
        Spectrum af = mLookup->AverageForwardScatteringAttenuation(thetaD);

        Spectrum sqrt1 = Sqrt(2.0 * Sqr(betaF) + Sqr(betaB));
        Spectrum sqrt2 = Sqrt(2.0 * Sqr(betaF) + 3.0 * Sqr(betaB));
        Spectrum abPow3 = Pow3(ab);

        Spectrum factor = Spectrum(1.0) + this->mDb * Sqr(af);
        Spectrum nom = ab * sqrt1 + abPow3 * sqrt2;
        Spectrum denom = ab + abPow3 * (2.0 * betaF + 3.0 * betaB);

        return factor * nom / denom;
    }

    Float DualScatteringBSDF::Pdf(const Vector3f &wo, const Vector3f & wi) const {

        return PiOver4;
    }

    std::string DualScatteringBSDF::ToString() const {
        return "DualScatteringBSDF";
    }

} // namespace pbrt
