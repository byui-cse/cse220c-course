COPTS=-Wall -g -std=c++20

TARGETS := \
	task-01 \
	task-02-1 task-02-2 task-02-3 task-02-4 task-02-5

all: $(TARGETS)
	cd map; $(MAKE)
	cd list; $(MAKE)
	cd vector; $(MAKE)

clean:
	-rm $(TARGETS)
	cd map; $(MAKE) clean
	cd list; $(MAKE) clean
	cd vector; $(MAKE) clean

task-01: task-01.cpp
	g++ $(COPTS) $^ -o $@

task-02-1: task-02-1.cpp
	g++ $(COPTS) $^ -o $@

task-02-2: task-02-2.cpp
	g++ $(COPTS) $^ -o $@

task-02-3: task-02-3.cpp
	g++ $(COPTS) $^ -o $@

task-02-4: task-02-4.cpp
	g++ $(COPTS) $^ -o $@

task-02-5: task-02-5.cpp
	g++ $(COPTS) $^ -o $@

