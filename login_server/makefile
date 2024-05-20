# Makefile for the login_server program

# 컴파일러와 컴파일 플래그 정의
CXX = g++
CXXFLAGS = -Ilogin_server -I./socket -I./user -I../utils -std=c++11 -Wall -Wextra

# 소스 파일과 객체 파일 목록 정의
SRCS =  main.cpp authenticate.cpp connection_handler.cpp \
		./socket/socket.cpp ./socket/bind.cpp ./socket/listen.cpp ./socket/accept.cpp \
		./user/add_user.cpp ./user/remove_user.cpp ./user/send_users.cpp \
		../utils/parseHeader.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# 실행 파일 이름
TARGET = server

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
debug: CXXFLAGS +=
