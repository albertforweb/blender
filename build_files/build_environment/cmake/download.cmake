# SPDX-License-Identifier: GPL-2.0-or-later

## Update and uncomment this in the release branch
# set(BLENDER_VERSION 3.1)

function(download_source dep)
  set(TARGET_FILE ${${dep}_FILE})
  set(TARGET_HASH_TYPE ${${dep}_HASH_TYPE})
  set(TARGET_HASH ${${dep}_HASH})
  if(PACKAGE_USE_UPSTREAM_SOURCES)
    set(TARGET_URI  ${${dep}_URI})
  elseif(BLENDER_VERSION)
    set(TARGET_URI  https://svn.blender.org/svnroot/bf-blender/tags/blender-${BLENDER_VERSION}-release/lib/packages/${TARGET_FILE})
  else()
    set(TARGET_URI  https://svn.blender.org/svnroot/bf-blender/trunk/lib/packages/${TARGET_FILE})
  endif()
  set(TARGET_FILE ${PACKAGE_DIR}/${TARGET_FILE})
  message("Checking source : ${dep} (${TARGET_FILE})")
  if(NOT EXISTS ${TARGET_FILE})
    message("Checking source : ${dep} - source not found downloading from ${TARGET_URI}")
    file(DOWNLOAD ${TARGET_URI} ${TARGET_FILE}
         TIMEOUT 1800  # seconds
         EXPECTED_HASH ${TARGET_HASH_TYPE}=${TARGET_HASH}
         TLS_VERIFY ON
         SHOW_PROGRESS
        )
  endif()
endfunction(download_source)

download_source(ZLIB)
download_source(OPENAL)
download_source(PNG)
download_source(JPEG)
download_source(BOOST)
download_source(BLOSC)
download_source(PTHREADS)
download_source(OPENEXR)
download_source(FREETYPE)
download_source(GLEW)
download_source(FREEGLUT)
download_source(ALEMBIC)
download_source(GLFW)
download_source(CLEW)
download_source(GLFW)
download_source(CUEW)
download_source(OPENSUBDIV)
download_source(SDL)
download_source(OPENCOLLADA)
download_source(OPENCOLORIO)
download_source(LLVM)
download_source(OPENMP)
download_source(OPENIMAGEIO)
download_source(TIFF)
download_source(OSL)
download_source(PYTHON)
download_source(TBB)
download_source(OPENVDB)
download_source(NANOVDB)
download_source(NUMPY)
download_source(LAME)
download_source(OGG)
download_source(VORBIS)
download_source(THEORA)
download_source(FLAC)
download_source(VPX)
download_source(OPUS)
download_source(X264)
download_source(XVIDCORE)
download_source(OPENJPEG)
download_source(FFMPEG)
download_source(FFTW)
download_source(ICONV)
download_source(SNDFILE)
download_source(WEBP)
download_source(SPNAV)
download_source(JEMALLOC)
download_source(XML2)
download_source(TINYXML)
download_source(YAMLCPP)
download_source(EXPAT)
download_source(PUGIXML)
download_source(FLEXBISON)
download_source(BZIP2)
download_source(FFI)
download_source(LZMA)
download_source(SSL)
download_source(SQLITE)
download_source(EMBREE)
download_source(USD)
download_source(OIDN)
download_source(LIBGLU)
download_source(MESA)
download_source(NASM)
download_source(XR_OPENXR_SDK)
download_source(WL_PROTOCOLS)
download_source(ISPC)
download_source(GMP)
download_source(POTRACE)
download_source(HARU)
download_source(ZSTD)
download_source(FLEX)
download_source(BROTLI)
download_source(FMT)
download_source(ROBINMAP)
download_source(IMATH)
download_source(PYSTRING)
download_source(LEVEL_ZERO)
