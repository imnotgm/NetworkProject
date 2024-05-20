# Makefile for the client program

# 컴파일러와 컴파일 플래그 정의
CXX = g++
CXXFLAGS = -I. -I./socket -I../utils -std=c++11 -Wall -Wextra

# 소스 파일과 객체 파일 목록 정의
SRCS =  main.cpp client.cpp login.cpp chat.cpp \
		./socket/socket.cpp ./socket/connect.cpp \
		../utils/parseHeader.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# 실행 파일 이름
TARGET = client

# 기본 타겟 (make만 실행할 때)
all: clean $(TARGET)

# 실행 파일을 만드는 규칙
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

# 개별 소스 파일을 객체 파일로 컴파일하는 규칙
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 정리 규칙
clean:
	rm -f $(OBJS) $(TARGET)

# 디버그 빌드
debug: CXXFLAGS += -g
debug: clean $(TARGET)

# 의존성 규칙 (자동 생성)
depend: $(SRCS)
	makedepend $(CXXFLAGS) $^

# Makefile에서 include 명령어는 여기에서 생성된 의존성을 포함할 수 있습니다.
#include depend.mk

# 자동 생성된 의존성을 삭제합니다.
.PHONY: clean depend
