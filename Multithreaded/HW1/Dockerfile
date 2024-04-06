FROM ubuntu:16.04
COPY . D:\Projects\Docker\HW_2
WORKDIR D:\Projects\Docker\HW_2
RUN apt update 
RUN apt install -y clang
RUN clang++ main.cpp -o HW2
CMD ["./HW2"]