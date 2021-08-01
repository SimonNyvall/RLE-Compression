FROM ubuntu

WORKDIR /app

RUN apt-get update && apt-get install build-essential clang -y

COPY . .

RUN echo "-=-=- Building with GCC -=-=-" && \
    g++ RleCompression.cpp -o RleCompression && \
    echo "-=-=- Building with Clang -=-=-" && \
    clang++ RleCompression.cpp -o RleCompression_clang && \
    echo "-=-=- Build done -=-=-" && \
    ls -la

ENTRYPOINT ["./RleCompression"]
