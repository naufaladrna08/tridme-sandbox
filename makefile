HEADERS = -I ../Core/include \
					-I ../vendors/glad/include \
					-I ../vendors/glfw/include \
					-I ../vendors/glm/glm \
					-I ../vendors/imgui \
					-I ../vendors/stbi

%.o: %.cpp
	@g++ -g -c $^ -o $@ $(HEADERS)
	@echo " [CC] $<"

%.o: %.c
	@gcc -g -c $^ -o $@ $(HEADERS)
	@echo " [CXX] $<"

main: main.o glad.o stb_image.o
	g++ -o $@ $^ $(HEADERS) ../Lib/libcore.so -lglfw3 -lGL -lXrandr -lX11 -lXi -ldl -lpthread
	@echo " [LINKING] main"

debug: main.o glad.o stb_image.o
	g++ -g -o $@ $^ $(HEADERS) .../Lib/libcore.so -lglfw3 -lGL -lXrandr -lX11 -lXi -ldl -lpthread

clean: 
	rm -rf main.o glad.o stb_image.o main debug libcore.so