CC = g++
FLAGS = -std=c++14 -O2

projectName = AdaBoost.out
sourceDir = SourceFiles
headerDir = HeaderFiles

objectFiles =  HeartDiseaseData.o #AdaBoost.o # Nodes.o Sample.o Tree.o
mainFile = $(sourceDir)/PSZT_pr2.cpp


all: $(projectName)

$(projectName): $(objectFiles)
	$(CC) $(FLAGS) $(mainFile) $(objectFiles) -o $@

HeartDiseaseData.o: $(headerDir)/HeartDiseaseData.h $(sourceDir)/HeartDiseaseData.cpp
	$(CC) $(FLAGS) -c $(headerDir)/HeartDiseaseData.h $(sourceDir)/HeartDiseaseData.cpp

#AdaBoost.o: $(headerDir)/AdaBoost.h
#	$(CC) $(FLAGS) -c $(headerDir)/AdaBoost.h

#Nodes.o: $(headerDir)/Nodes.h
#	$(CC) $(FLAGS) -c $(headerDir)/Nodes.h

#Sample.o: $(headerDir)/Sample.h
#	$(CC) $(FLAGS) -c $(headerDir)/Sample.h

#Tree.o: $(headerDir)/Tree.h
#	$(CC) $(FLAGS) -c $(headerDir)/Tree.h

#$(headerDir)/AdaBoost.h $(headerDir)/HeartDiseaseData.h $(headerDir)/Nodes.h $(headerDir)/Sample.h $(headerDir)/Tree.h
#	$(CC) $(FLAGS) $(headerDir)/AdaBoost.h $(headerDir)/HeartDiseaseData.h $(headerDir)/Nodes.h $(headerDir)/Sample.h $(headerDir)/Tree.h -o $(projectName)

clean:
	rm -f $(projectName) *.o
	cd $(sourceDir) && rm -f *.h.gch
	cd $(headerDir) && rm -f *.h.gch
