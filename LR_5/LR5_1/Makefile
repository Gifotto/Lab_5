# Имя итогового исполняемого файла
TARGET = train_manager

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Список исходных файлов
SRCS = main.cpp train.cpp train_manager.cpp commands.cpp

# Объектные файлы (из .cpp -> .o)
OBJS = $(SRCS:.cpp=.o)

# Цель по умолчанию — сборка всего
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJS)
\t$(CXX) $(CXXFLAGS) -o $@ $^

# Правило сборки объектных файлов
%.o: %.cpp
\t$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка временных файлов
clean:
\trm -f $(OBJS) $(TARGET)
