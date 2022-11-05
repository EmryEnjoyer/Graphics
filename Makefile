CPPFLAGS := -lglut -lGL -lGLU
DEPS := UtilityFunctions.cpp camera.cpp ObjectLoader.cpp SceneObject.cpp
%.o: %.cpp
	g++ $< -g $(DEPS) $(CPPFLAGS) -o $@