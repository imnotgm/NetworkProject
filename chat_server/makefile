# Makefile for the login_server program

# 컴파일러와 컴파일 플래그 정의
CXX = g++
CXXFLAGS = -Ichat_server -I./socket -I./chat_group -I./list -I../login_server/user -I../include -I../include/utils -I../include/rapidjson -std=c++11 -Wall -Wextra

# 소스 파일과 객체 파일 목록 정의
SRCS =  main.cpp conn_handler.cpp msg_handler.cpp \
        ./socket/socket.cpp ./socket/bind.cpp ./socket/listen.cpp ./socket/accept.cpp \
        ./chat_group/ChatGroup.cpp ./chat_group/join.cpp ./chat_group/leave.cpp ./chat_group/broadcast.cpp ./chat_group/empty.cpp \
		./list/user_list.cpp ./list/live_chat_list.cpp \
        ../include/utils/countSubstr.cpp ../include/utils/parseHeader.cpp ../include/utils/split.cpp

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
debug: CXXFLAGS += -g
all: $(TARGET)
