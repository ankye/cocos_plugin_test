workspace=`pwd`
rm -rf build
mkdir -p build
projectName="CC_PLUGIN_TP__"
source "/Users/a1021500561/emsdk/emsdk_env.sh"

cd build && emcmake cmake ../ && emmake make -j8 
##for cocos


filename="lib${projectName}.js";
base64 -i ${projectName}.wasm -o ${projectName}.base64
header='var RAWWasmBinaryFile = "data:application/octet-stream;base64,'
content=`cat ${projectName}.base64`;

echo $header$content'";' > $filename;
cat ${projectName}.js >> $filename;

sed -i '' "s/\'${projectName}.wasm\'/RAWWasmBinaryFile/" $filename;


outname="${projectName}.js"

a1=`cat ${workspace}/post/post.js`;
if [ "$1" == "mjs" ]; then
a1=`cat ${workspace}/post/post.mjs`;
outname="${projectName}.mjs"
fi

echo "var version='${projectName} $(date +%F+%T)';" >> $filename
echo $a1 >> $filename;

cp $filename $workspace/dist/
cd $workspace
echo "\n>>>>>build success"