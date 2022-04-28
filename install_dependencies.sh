#!/bin/bash
set -e #abort with error if any command returns with something other than zero

############
# Install script for v3dd dependencies
# Run "$> sudo ./install_dependencies.sh" to install system wide
# Run "$> ./install_dependencies.sh <path_to_prefix>" to install to a local prefix
############

function build {

  if [ -d $3 ] 
  then
    echo "Directory $3 already exists. " 
    read -r -p "Do you want to delete and re-download $3? [y/N] " response
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])+$ ]]
    then
     rm -rf $3
    else
      echo "Aborting!"
      exit -1
    fi
  fi
  git clone --branch $2 $1 $3
  mkdir $3/build
  cd $3/build
  cmake .. $4
  make install
  cd ../../
}



PREFIX=""
ABS_PREFIX=""
if [ "$#" -eq 1 ]; then
ABS_PREFIX=`readlink -f $1`
PREFIX="-DCMAKE_INSTALL_PREFIX=$ABS_PREFIX"

echo "" > env.sh #create empty env.sh
echo "export CMAKE_PREFIX_PATH=$ABS_PREFIX" >> env.sh
echo "export PKG_CONFIG_PATH=$ABS_PREFIX/lib/pkgconfig:$ABS_PREFIX/share/pkgconfig:$ABS_PREFIX/lib64/pkgconfig:\$PKG_CONFIG_PATH" >> env.sh
echo "export LD_LIBRARY_PATH=$ABS_PREFIX/lib:$ABS_PREFIX/lib64:\$LD_LIBRARY_PATH" >> env.sh
echo "export PATH=$ABS_PREFIX/bin:\$PATH" >> env.sh
echo "export OROCOS_TARGET=gnulinux" >> env.sh
echo "export VIZKIT_PLUGIN_RUBY_PATH=$ABS_PREFIX/lib" >> env.sh

source env.sh
else

echo "Please specify a prefix. If you want system wide installation use '/usr/local' as prefix."
exit -1
  
fi

build https://github.com/rock-core/base-cmake.git master base-cmake "$PREFIX"
build https://github.com/rock-core/base-logging.git master base-logging "$PREFIX"
build https://github.com/rock-core/base-types.git "feature/qt5" base-types "-DBINDINGS_RUBY=OFF -DUSE_SISL=OFF -DROCK_VIZ_ENABLED=TRUE $PREFIX"
build https://github.com/rock-core/gui-osgviz.git master gui-osgviz "$PREFIX"
build https://github.com/orocos-toolchain/rtt.git master rtt "$PREFIX"
build https://github.com/rock-core/gui-vizkit3d.git "feature/qt5" gui-vizkit3d "$PREFIX"







