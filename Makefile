CC = g++
FLAGS = -std=c++14 -O2

projectName = AdaBoost.out
sourceDir = SourceFiles
headerDir = HeaderFiles

objectFiles =  HeartDiseaseData.o
mainFile = $(sourceDir)/PSZT_pr2.cpp


all: $(projectName)

$(projectName): $(objectFiles)
	$(CC) $(FLAGS) $(mainFile) $(objectFiles) -o $@

HeartDiseaseData.o: $(headerDir)/HeartDiseaseData.h $(sourceDir)/HeartDiseaseData.cpp
	$(CC) $(FLAGS) -c $(headerDir)/HeartDiseaseData.h $(sourceDir)/HeartDiseaseData.cpp

clean:
	rm -f $(projectName) *.o
	cd $(sourceDir) && rm -f *.h.gch
	cd $(headerDir) && rm -f *.h.gch
