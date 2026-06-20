# Use an official GCC image
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy source files into the container
COPY . .

# Create users directory if not present
RUN mkdir -p users

# Compile the project
RUN g++ -std=c++17 -o netflix main.cpp

# Set the entrypoint to run the CLI
CMD ["./netflix"]
