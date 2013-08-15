FLAGS = -g -O3
CX = g++
jnews: jnews.cpp stemmer.o analyzer.o svm_predict.o svm.o svm.h
	$(CX) jnews.cpp stemmer.o analyzer.o svm_predict.o svm.o -o jnews -g
stemmer.o: stemmer.cpp stemmer.h
	$(CX) -c stemmer.cpp -o stemmer.o -g
analyzer.o: analyzer.cpp analyzer.h
	$(CX) -c analyzer.cpp -o analyzer.o -g
svm_predict.o: svm_predict.cpp svm.h
	$(CX) -c svm_predict.cpp -o svm_predict.o -g
svm.o: svm.cpp svm.h
	$(CX) -c svm.cpp -o svm.o -g
clean:
	rm svm.o svm_predict.o analyzer.o stemmer.o jnews
