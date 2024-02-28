#include <iostream>

#include "crossbar.h"
#include "globalvar.h"  // need to be there lest main segfaults
#include "Ucache.h"  // for init_tech_params

int main(int argc, char* argv[])
{
  if (argc != 1+4)
  {
    std::cout << "Usage: crossbar <tech_node_in_nm> <width_in_bits> <n_inputs> <n_outputs>"
              << std::endl;
    return 0;
  }

  const double technology = std::stod(argv[1])/1000; // input in nm, mcpat in um
  const int width_in_bits = std::stoi(argv[2]);
  const int n_inputs = std::stoi(argv[3]);
  const int n_outputs = std::stoi(argv[4]);

  g_ip = new InputParameter();
  g_ip->F_sz_um = technology;
  g_ip->temp = 300+60;
  init_tech_params(technology, false);
  Wire winit; // Do not delete this line; it initializes wires.

  Crossbar crossbar(n_inputs, n_outputs, width_in_bits);
  crossbar.compute_power();

  std::cout << "Energy (J/access): " << crossbar.power.readOp.dynamic << std::endl;
  std::cout << "Area (um^2): " << crossbar.area.get_area() << std::endl;
}
