echo "building assimp with ninja then running tests if successful"
cd ..


if ninja ; then
	echo "Running tests because we built!"
	cd bin
	./run-scale-test.sh
else
	cd bin
	echo "Build failed, tests cannot run!"
fi


