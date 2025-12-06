CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++11
TARGET = word_count
SOURCES = main.cpp FileReader.cpp WordTokenizer.cpp FrequencyCounter.cpp CSVWriter.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
