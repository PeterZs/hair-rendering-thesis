rm output/*.pbrt

### ================================================================
### Environment map Venice (looking at it from backside)
### ================================================================

# subway
# prepare --input woman-head.scene --output output/eon_sub_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_sub_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_sub_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_sub_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_sub_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_sub_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=

# prepare --input woman-head.scene --output output/uniform_sub_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_sub_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_sub_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_sub_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_sub_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_sub_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/subway.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=

#prepare --input woman-head.scene --output output/uniform_sub_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=1,useDistantLight=#,useAreaLight=#,useInfiniteLight=

prepare --input woman-head.scene --output output/eon_sub_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/eon_sub_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/eon_sub_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/eon_sub_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/eon_sub_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/eon_sub_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=

prepare --input woman-head.scene --output output/uniform_sub_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/uniform_sub_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/uniform_sub_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/uniform_sub_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/uniform_sub_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
prepare --input woman-head.scene --output output/uniform_sub_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props hdr-settings/subway.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=

# # # venice
# prepare --input woman-head.scene --output output/eon_v_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_v_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_v_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_v_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_v_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_v_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=

# prepare --input woman-head.scene --output output/uniform_v_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_v_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_v_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_v_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_v_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_v_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/venice.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=


# # office
# prepare --input woman-head.scene --output output/eon_os_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_os_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_os_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_os_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_os_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=deon,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/eon_os_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=deon,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=

# prepare --input woman-head.scene --output output/uniform_os_brown1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=brown1,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_os_brown2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=brown2,material_name=brown_hair2,model_hair_filename=wStraight,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_os_blonde1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=blonde1,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_os_blonde2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=blonde2,material_name=light_blonde_hair,model_hair_filename=wWavyThin,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_os_black1.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=black1,material_name=black_hair,model_hair_filename=wCurly.25,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,useDistantLight=#,useAreaLight=#,useInfiniteLight=
# prepare --input woman-head.scene --output output/uniform_os_black2.pbrt --propertyfiles base.properties states/elevated-up-view.props states/test.props hdr-settings/office_square.props --properties image_output_basename=black2,material_name=black_hair,model_hair_filename=wCurly.z,shader=dualscattering,samplingMethod=uniform,pixelsamples=32,model_rotation=0,useDistantLight=#,useAreaLight=#,useInfiniteLight=