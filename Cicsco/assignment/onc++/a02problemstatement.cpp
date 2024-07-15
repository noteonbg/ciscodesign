/*


Problem Statement: Circuit Simulation and Analysis Tool
Objective:
Develop a C++ program that simulates and analyzes simple electronic circuits. The program should read a circuit description from a file, simulate the circuit to compute node voltages and branch currents, and generate a report summarizing the results.

Data Format:
The input file (circuit_description.txt) contains a list of components and their connections in the following format:

R1 1 2 1000
R2 2 0 2000
V1 1 0 5

Component types: Resistor (R), Voltage Source (V).
Format: ComponentName Node1 Node2 Value
Node 0 represents the ground.

Functional Requirements:

File Reading: Read the circuit description from circuit_description.txt.
Data Storage: Store the components and their connections in appropriate data structures.
Simulation:
Formulate the circuit equations using Kirchhoff's Current Law (KCL) and Kirchhoff's Voltage Law (KVL).
Solve the system of linear equations to find node voltages.
Calculate branch currents based on node voltages.
Reporting:
Generate a summary report displaying node voltages and branch currents.
User Interface:
Provide a command-line interface to specify the input file and view the report.
Constraints:

The program should handle simple linear circuits with resistors and independent voltage sources.
The program must be efficient in solving the system of equations, even for larger circuits.
Extra Credit:

Support additional component types (e.g., capacitors, inductors, current sources).
Implement transient analysis for circuits with capacitors and inductors.
Provide visualization of the circuit and simulation results.
Hints:

Use data structures like vectors or maps to store the circuit components and their connections.
Implement matrix operations to solve the system of linear equations (e.g., Gaussian elimination).
Structure the program with modular functions to handle different tasks
 (e.g., reading data, formulating equations, solving equations, generating reports).


*/


#if 0


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <Eigen/Dense>

// Define a structure to hold component data
struct Component {
    std::string type;
    std::string name;
    int node1;
    int node2;
    double value;
};

// Function prototypes
bool readCircuitDescription(const std::string& filename, std::vector<Component>& components);
void formulateCircuitEquations(const std::vector<Component>& components, Eigen::MatrixXd& A, Eigen::VectorXd& b);
void solveCircuit(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& nodeVoltages);
void generateReport(const std::vector<Component>& components, const Eigen::VectorXd& nodeVoltages);

int main() {
    std::string filename = "circuit_description.txt";
    std::vector<Component> components;

    if (!readCircuitDescription(filename, components)) {
        std::cerr << "Failed to read circuit description from file: " << filename << std::endl;
        return 1;
    }

    // Determine the number of nodes (highest node number)
    int numNodes = 0;
    for (const auto& component : components) {
        numNodes = std::max(numNodes, std::max(component.node1, component.node2));
    }

    // Formulate circuit equations
    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(numNodes, numNodes);
    Eigen::VectorXd b = Eigen::VectorXd::Zero(numNodes);
    formulateCircuitEquations(components, A, b);

    // Solve circuit equations
    Eigen::VectorXd nodeVoltages(numNodes);
    solveCircuit(A, b, nodeVoltages);

    // Generate report
    generateReport(components, nodeVoltages);

    return 0;
}

bool readCircuitDescription(const std::string& filename, std::vector<Component>& components) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        Component component;
        ss >> component.name >> component.node1 >> component.node2 >> component.value;

        if (component.name[0] == 'R') {
            component.type = "Resistor";
        } else if (component.name[0] == 'V') {
            component.type = "Voltage Source";
        } else {
            continue;  // Skip unknown components
        }

        components.push_back(component);
    }

    return true;
}

void formulateCircuitEquations(const std::vector<Component>& components, Eigen::MatrixXd& A, Eigen::VectorXd& b) {
    for (const auto& component : components) {
        if (component.type == "Resistor") {
            int n1 = component.node1 - 1;
            int n2 = component.node2 - 1;
            double conductance = 1.0 / component.value;

            if (n1 >= 0) {
                A(n1, n1) += conductance;
                if (n2 >= 0) {
                    A(n1, n2) -= conductance;
                }
            }

            if (n2 >= 0) {
                A(n2, n2) += conductance;
                if (n1 >= 0) {
                    A(n2, n1) -= conductance;
                }
            }
        } else if (component.type == "Voltage Source") {
            int n1 = component.node1 - 1;
            int n2 = component.node2 - 1;

            if (n1 >= 0) {
                b(n1) -= component.value;
            }

            if (n2 >= 0) {
                b(n2) += component.value;
            }
        }
    }
}

void solveCircuit(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, Eigen::VectorXd& nodeVoltages) {
    nodeVoltages = A.colPivHouseholderQr().solve(b);
}

void generateReport(const std::vector<Component>& components, const Eigen::VectorXd& nodeVoltages) {
    std::cout << "Circuit Simulation Report\n";
    std::cout << "========================\n";
    for (int i = 0; i < nodeVoltages.size(); ++i) {
        std::cout << "Node " << (i + 1) << " Voltage: " << nodeVoltages(i) << " V\n";
    }

    std::cout << "\nBranch Currents:\n";
    for (const auto& component : components) {
        if (component.type == "Resistor") {
            int n1 = component.node1 - 1;
            int n2 = component.node2 - 1;
            double voltage1 = (n1 >= 0) ? nodeVoltages(n1) : 0.0;
            double voltage2 = (n2 >= 0) ? nodeVoltages(n2) : 0.0;
            double current = (voltage1 - voltage2) / component.value;
            std::cout << component.name << ": " << current << " A\n";
        }
    }
}

#endif
