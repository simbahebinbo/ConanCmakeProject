#include <iostream>
#include <vector>
#include <random>

// Define a struct to represent a particle
struct Particle {
  std::vector<double> position;  // Current position of the particle
  std::vector<double> velocity;  // Current velocity of the particle
  std::vector<double> best_position;  // Best position found by the particle
  double best_fitness;            // Fitness value at the best position

  //add destructor to free memory
    ~Particle() {
        position.clear();
        velocity.clear();
        best_position.clear();
    }
};

// Function to calculate the fitness of a particle (replace with your objective function)
 // Implement your objective function here
  // This function should take the particle's position as input and return a fitness value
  // Lower values indicate better solutions
double fitnessFunction(const std::vector<double>& position) {
    double sum = 0.0;
    for (double x : position) {
        sum += x * x;
    }
    return sum; 
}

// Function to update particle velocity
void updateVelocity(Particle& particle, const std::vector<double>& global_best,
                     double w, double c1, double c2) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  int n = particle.position.size();
  for (int i = 0; i < n; ++i) {
    double r1 = dis(gen);
    double r2 = dis(gen);
    particle.velocity[i] = w * particle.velocity[i] +
                            c1 * r1 * (particle.best_position[i] - particle.position[i]) +
                            c2 * r2 * (global_best[i] - particle.position[i]);
  }
}

// Function to update particle position
void updatePosition(Particle& particle, const std::vector<double>& lower_bounds,
                     const std::vector<double>& upper_bounds) {
  int n = particle.position.size();
  for (int i = 0; i < n; ++i) {
    particle.position[i] += particle.velocity[i];

    // Handle boundary conditions (optional)
    if (particle.position[i] < lower_bounds[i]) {
      particle.position[i] = lower_bounds[i];
    } else if (particle.position[i] > upper_bounds[i]) {
      particle.position[i] = upper_bounds[i];
    }
  }
}

int main() {
  // Define swarm parameters
  int num_particles = 100;
  int n = 5;  // Number of dimensions in the search space (modify as needed)
  double w = 0.729;  // Inertia weight
  double c1 = 1.49618;  // Cognitive learning rate
  double c2 = 1.49618;  // Social learning rate

  // Define search space boundaries (modify as needed)
  std::vector<double> lower_bounds(n, -10.0);
  std::vector<double> upper_bounds(n, 10.0);

  // Initialize random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(lower_bounds[0], upper_bounds[0]);

  // Initialize the swarm
  std::vector<Particle> swarm(num_particles);
  for (Particle& particle : swarm) {
    particle.position.resize(n);
    particle.velocity.resize(n);
    particle.best_position.resize(n);
    for (int i = 0; i < n; ++i) {
      particle.position[i] = dis(gen);
      particle.velocity[i] = 0.0;
    }
    particle.best_position = particle.position;
    particle.best_fitness = fitnessFunction(particle.position);
  }
  std::cout << "Swarm initialized" << std::endl;
  

  // Initialize global best
  std::vector<double> global_best(n);
  double global_fitness = std::numeric_limits<double>::infinity();
  for (const Particle& particle : swarm) {
    if (particle.best_fitness < global_fitness) {
      global_fitness = particle.best_fitness;
      global_best = particle.best_position;
    }
  }

  // PSO
    int max_iterations = 1000;
    for (int iter = 0; iter < max_iterations; ++iter) {
        for (Particle& particle : swarm) {
            double fitness = fitnessFunction(particle.position);
            if (fitness < particle.best_fitness) {
                particle.best_fitness = fitness;
                particle.best_position = particle.position;
            }
            if (fitness < global_fitness) {
                global_fitness = fitness;
                global_best = particle.position;
            }
            updateVelocity(particle, global_best, w, c1, c2);
            updatePosition(particle, lower_bounds, upper_bounds);
        }
    }
}