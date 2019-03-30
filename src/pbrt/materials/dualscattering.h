
/*
 Dual hair scattering algorithm for PBRT
 */

#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef PBRT_MATERIALS_DUALSCATTERING_H
#define PBRT_MATERIALS_DUALSCATTERING_H

// materials/dualscattering.h*
#include "pbrt.h"
#include "material.h"
#include "marschner.h"

namespace pbrt {

// PlasticMaterial Declarations
class DualscatteringMaterial : public Material {
  public:
    // PlasticMaterial Public Methods
    DualscatteringMaterial(Float eta, MarschnerMaterial* marschnerMaterial, 
            Float alphaR, Float alphaTT, Float alphaTRT, 
            Float betaR, Float betaTT, Float betaTRT) 
    : mEta(eta), mMarschnerMaterial(marschnerMaterial), 
            mAlphaR(alphaR), mAlphaTT(alphaTT), mAlphaTRT(alphaTRT), 
            mBetaR(betaR), mBetaTT(betaTT), mBetaTRT(betaTRT) {}
        
    void ComputeScatteringFunctions(SurfaceInteraction *si, MemoryArena &arena,
                                    TransportMode mode,
                                    bool allowMultipleLobes) const;

  private:
      MarschnerMaterial* mMarschnerMaterial = nullptr;
      Float mEta;
      Float mAlphaR, mAlphaTT, mAlphaTRT, mBetaR, mBetaTT, mBetaTRT;
};

struct GlobalScatteringInformation {
    Float transmittance, variance, directIlluminationFraction;
};

class DualScatteringBSDF : public BxDF {
public:
    DualScatteringBSDF(const SurfaceInteraction& si, Float eta,
            MarschnerBSDF* marschnerBSDF,
            Float alphaR, Float alphaTT, Float alphaTRT,
            Float betaR, Float betaTT, Float betaTRT);
    
    /**
         * (Required) Returns the value of the distribution function for the given pair of directions
         *
         * @param wo outgoing direction
         * @param wi incoming direction
         * @return
         */
        virtual Spectrum f(const Vector3f &wo, const Vector3f &wi) const;
        
        /**
         * Returns the value of the distribution function for the given pair of directions.
         *
         * Used for handling scattering that is described by delta distributions
         * as well as for randomly sampling directions from BxDFs that scatter
         * light along multiple directions.
         *
         * @param wo outgoing direction
         * @param wi incoming direction
         * @param sample
         * @param pdf
         * @param sampledType
         * @return
         */
        virtual Spectrum Sample_f(const Vector3f &wo, Vector3f *wi, const Point2f &sample, Float *pdf, BxDFType *sampledType = nullptr) const;
        
        /**
         * Returns the probability density function between the incoming and outgoing direction.
         * In other words, how likely is it that incoming radiance is reflected
         * (or refracted) towards the outgoing direction.
         * @param wo
         * @param wi
         * @return 
         */       
        virtual Float Pdf(const Vector3f &wo, const Vector3f &wi) const;
        
        /**
         * 
         * @return 
         */
        virtual std::string ToString() const;
        
        // Not implemented for now
        //virtual Spectrum rho(const Vector3f &wo, int nSamples, const Point2f *samples) const;
        //virtual Spectrum rho(int nSamples, const Point2f *samples1, const Point2f *samples2) const;
    
private:
    MarschnerBSDF* mMarschnerBSDF;
    Float mEta;
    Point3f mPosition;
    Float mDf, mDb;
    Float mBetaR, mBetaTT, mBetaTRT;
    Float mAlphaR, mAlphaTT, mAlphaTRT;
    
    void GatherGlobalScatteringInformation(const Vector3f& wd, GlobalScatteringInformation& gsi) const;
    int FindScatteringCount(const Vector3f &wd) const;
    
    Float ForwardScatteringTransmittance() const;
    Float ForwardScatteringVariance(Float theta) const;
    
    Float BackscatteringAttenuation(Float theta) const;
    Float BackscatteringMean(Float theta) const;
    Float BackscatteringVariance(Float theta) const;  
    
    Float MG_r(Float theta, Float forwardScatteringVariance) const;
    Float MG_tt(Float theta, Float forwardScatteringVariance) const;
    Float MG_trt(Float theta, Float forwardScatteringVariance) const;
    
    Spectrum EvaluateForwardScatteredMarschner(Float theta_r, Float theta_h,
        Float theta_d, Float phi, Float forwardScatteredVariance) const;
    
};

DualscatteringMaterial *CreateDualscatteringMaterial(const TextureParams &mp);

}  // namespace pbrt

#endif  // PBRT_MATERIALS_DUALSCATTERING_H
