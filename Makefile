CXX=g++
LD=g++
SRC=src
CFLAGS=-Wall -pedantic -ggdb
LIBS=-lsfml-graphics -lsfml-system -lsfml-window -lsfgui
	
NM=ParticleSystem
all: compile 

compile: $(NM)

$(NM): main.o MovingObject.o AutomatedMovingObject.o GravityPoint.o AutomatedGravityPoint.o MouseControllGravityPoint.o ParticleSystem.o Color.o Gradient.o ParticleColorManager.o Particle.o ParticleGroup.o Shape.o ShapeRectangle.o Point.o ParticleSfmlPrimitive.o ParticleSfmlSprite.o ParticlePhysics.o ShapeCircle.o Emitter.o 
	$(LD) -o $(NM) main.o MovingObject.o AutomatedMovingObject.o GravityPoint.o AutomatedGravityPoint.o MouseControllGravityPoint.o ParticleSystem.o Color.o Gradient.o ParticleColorManager.o Particle.o ParticleGroup.o Shape.o ShapeRectangle.o Point.o ParticleSfmlPrimitive.o ParticleSfmlSprite.o ParticlePhysics.o ShapeCircle.o Emitter.o $(LIBS)


main.o: $(SRC)/main.cpp $(SRC)/ParticleSystem.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

MovingObject.o: $(SRC)/MovingObject.cpp $(SRC)/MovingObject.h  
	$(CXX) $(CFLAGS) -c -o $@ $<
	
AutomatedMovingObject.o: $(SRC)/AutomatedMovingObject.cpp $(SRC)/AutomatedMovingObject.h  
	$(CXX) $(CFLAGS) -c -o $@ $<

GravityPoint.o: $(SRC)/GravityPoint.cpp $(SRC)/GravityPoint.h  
	$(CXX) $(CFLAGS) -c -o $@ $<

AutomatedGravityPoint.o: $(SRC)/AutomatedGravityPoint.cpp $(SRC)/AutomatedGravityPoint.h  
	$(CXX) $(CFLAGS) -c -o $@ $<

MouseControllGravityPoint.o: $(SRC)/MouseControllGravityPoint.cpp $(SRC)/MouseControllGravityPoint.h  
	$(CXX) $(CFLAGS) -c -o $@ $<

ParticleSystem.o: $(SRC)/ParticleSystem.cpp $(SRC)/ParticleSystem.h $(SRC)/Particle.h $(SRC)/ParticleGroup.h  $(SRC)/Color.h $(SRC)/Color.h  $(SRC)/Gradient.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

Color.o: $(SRC)/Color.cpp $(SRC)/Color.h  
	$(CXX) $(CFLAGS) -c -o $@ $<

Gradient.o: $(SRC)/Gradient.cpp $(SRC)/Color.h $(SRC)/Gradient.h 
	$(CXX) $(CFLAGS) -c -o $@ $<
	
ParticleColorManager.o: $(SRC)/ParticleColorManager.cpp $(SRC)/ParticleColorManager.h $(SRC)/Color.h  $(SRC)/ParticleGroup.h 
	$(CXX) $(CFLAGS) -c -o $@ $<
	
Particle.o: $(SRC)/Particle.cpp $(SRC)/Particle.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

ParticlePhysics.o: $(SRC)/ParticlePhysics.cpp $(SRC)/ParticlePhysics.h  $(SRC)/Particle.h
	$(CXX) $(CFLAGS) -c -o $@ $<
	
ParticleGroup.o: $(SRC)/ParticleGroup.cpp $(SRC)/ParticleGroup.h  $(SRC)/Particle.h  $(SRC)/ParticlePhysics.h
	$(CXX) $(CFLAGS) -c -o $@ $<
	
Shape.o: $(SRC)/Shape.cpp $(SRC)/Shape.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ShapeRectangle.o: $(SRC)/ShapeRectangle.cpp $(SRC)/ShapeRectangle.h $(SRC)/Shape.h 
	$(CXX) $(CFLAGS) -c -o $@ $<
	
ShapeCircle.o: $(SRC)/ShapeCircle.cpp $(SRC)/ShapeCircle.h $(SRC)/Shape.h 
	$(CXX) $(CFLAGS) -c -o $@ $<
	
Emitter.o: $(SRC)/Emitter.cpp $(SRC)/Emitter.h $(SRC)/ShapeCircle.cpp $(SRC)/ShapeCircle.h $(SRC)/Shape.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

Point.o: $(SRC)/Point.cpp $(SRC)/Point.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

ParticleSfmlPrimitive.o: $(SRC)/ParticleSfmlPrimitive.cpp $(SRC)/ParticleSfmlPrimitive.h $(SRC)/Particle.h
	$(CXX) $(CFLAGS) -c -o $@ $<

ParticleSfmlSprite.o: $(SRC)/ParticleSfmlSprite.cpp $(SRC)/ParticleSfmlSprite.h $(SRC)/Particle.h
	$(CXX) $(CFLAGS) -c -o $@ $<
		
	
clean:
	rm -f *.o $(NM)

run:
	./$(NM)

 
