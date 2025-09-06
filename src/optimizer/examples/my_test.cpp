#include <psocpp.h>

// Implement an objective functor.
struct MyTest
{
    template<typename Derived>
    double operator()(const Eigen::MatrixBase<Derived> &xval) const
    {
        return pow((xval(0)-1), 2) + pow((xval(1)+1.1), 2) + pow(xval(2), 2) + pow((xval(3) + xval(4) + xval(5)), 2);
    }
};

int main()
{
    // Create optimizer object with MyTest functor as objective.
    
    pso::ParticleSwarmOptimization<double, MyTest> optimizer;

    // Set number of iterations as stop criterion.
    // Set it to 0 or negative for infinite iterations (default is 0).
    optimizer.setMaxIterations(1000);

    // Set the minimum change of the x-values (particles) (default is 1e-6).
    // If the change in the current iteration is lower than this value, then
    // the optimizer stops minimizing.
    optimizer.setMinParticleChange(1e-6);

    // Set the minimum change of the function values (default is 1e-6).
    // If the change in the current iteration is lower than this value, then
    // the optimizer stops minimizing.
    optimizer.setMinFunctionChange(1e-6);

    // Set the number of threads used for evaluation (OpenMP only).
    // Set it to 0 or negative for auto detection (default is 1).
    optimizer.setThreads(1);

    // Turn verbosity on, so the optimizer prints status updates after each
    // iteration.
    optimizer.setVerbosity(2);

    // Set the bounds in which the optimizer should search.
    // Each column vector defines the (min, max) for each dimension  of the
    // particles.
    Eigen::MatrixXd bounds(2, 6);
    bounds <<   -2, -3, -1, -1, -1, -1,
                4, 3, 1, 1, 1, 1;

    // start the optimization with a particle count
    auto result = optimizer.minimize(bounds, 1000);

    std::cout << "Done! Converged: " << (result.converged ? "true" : "false")
        << " Iterations: " << result.iterations << std::endl;

    // do something with final function value
    std::cout << "Final fval: " << result.fval << std::endl;

    // do something with final x-value
    std::cout << "Final xval: " << result.xval.transpose() << std::endl;

    return 0;
}
