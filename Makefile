OBJ = obj/model.o\
	  obj/render.o\
	  obj/main.o

.PHONY = clean run


obj/run:$(OBJ)
	mkdir -p $(@D)
	g++ $^ -o $@

obj/main.o: main.cpp
	mkdir -p $(@D)
	g++ -c $^ -o $@

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ -c $^ -o $@

clean: obj
	rm -rf obj

run: obj/run
	@obj/run