# Quick build for macOS/Linux with raylib installed via pkg-config.
CXX = c++
CPPFLAGS += $(shell pkg-config --cflags raylib)
CXXFLAGS += -std=c++17 -O2 -Wall -Wextra -Wpedantic
LDLIBS += $(shell pkg-config --libs raylib)
SOURCES = main.cpp GameController.cpp HUD.cpp MissionLog.cpp Obstacle.cpp PlayerShip.cpp RescueTarget.cpp
HEADERS = $(wildcard *.h)

.PHONY: all run
all: build/blackspace

build/blackspace: $(SOURCES) $(HEADERS)
	mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) $(LDLIBS) -o $@

run: build/blackspace
	./build/blackspace
