


function download_imgui {
    mkdir -p deps
    cd deps
    git clone https://github.com/ocornut/imgui.git
    cd imgui
    git checkout c7d3d22ae1e2b8f84ae30a922099873d5016e6d6
    cd ../../
}

function download_chibi {
    mkdir -p deps
    cd deps
    git clone https://github.com/ashinn/chibi-scheme.git
    cd chibi-scheme
    git checkout da53f46c93477a920e2e6b55c96c793cbd955fb8
    cd ../../
}

function download_setup_cimgui {
    cd deps/
    git clone https://github.com/dearimgui/dear_bindings.git
    wget --no-check-certificate https://www.dabeaz.com/ply/ply-3.11.tar.gz
    tar -xvzf ply-3.11.tar.gz
    cd ../
    mkdir deps/cimgui/
    PYTHONPATH=deps/ply-3.11:$PYTHONPATH python deps/dear_bindings/dear_bindings.py -o deps/cimgui/cimgui deps/imgui/imgui.h
    g++ -c deps/cimgui/cimgui.cpp -Ideps/cimgui/ -Ideps/imgui/ -o deps/cimgui/cimgui.o
}

function patch_imgui {
    echo "patch_imgui"
    cd deps/imgui/
    git apply ../../patches/imgui.patch
    cd ../../
}

function patch_chibi {
    echo "patch_chibi"
    cd deps/chibi-scheme/
    git apply ../../patches/chibi.patch
    cd ..
    mv chibi-scheme chibi-scheme-dynamic
    cp -r chibi-scheme-dynamic chibi-scheme-static
    cd ..
}

function build_dynamic_chibi {
    cd deps/chibi-scheme-dynamic/
    make -j8
    cd ../../
}
    
function link_libs {
    ln -s `pwd`/src/lib/imgui/ `pwd`/deps/chibi-scheme-static/lib/imgui
    ln -s `pwd`/src/lib/imgui.sld `pwd`/deps/chibi-scheme-static/lib/imgui.sld    
}


download_imgui
download_chibi
download_setup_cimgui

patch_imgui
patch_chibi
link_libs

build_dynamic_chibi

mkdir -p build/


