#include <iostream>

#include "interconnect.h"
#include "globalvar.h"  // need to be there lest main segfaults
#include "Ucache.h"  // for init_tech_params

int main(int argc, char* argv[])
{
  if (argc != 1+4)
  {
    std::cout << "Usage: interconnect <tech_node_in_nm> <width_in_bits> <link_len_in_um> <overlapped_portion>"
              << std::endl;
    return 0;
  }

  const double technology = std::stod(argv[1])/1000; // input in nm, mcpat in um
  const int width_in_bits = std::stoi(argv[2]);
  const int link_len = std::stoi(argv[3]);
  const double overlapped_portion = std::stod(argv[4]);

  g_ip = new InputParameter();
  g_ip->F_sz_um = technology;
  g_ip->temp = 300+60;
  init_tech_params(technology, false);
  Wire winit; // Do not delete this line; it initializes wires.

  std::cerr.setstate(std::ios_base::failbit);  // silences warning about incomplete config (but which we do not need)
  interconnect interconnect("links", Uncore_device, 1, 1, width_in_bits, link_len, g_ip, 3, true, overlapped_portion);
  std::cerr.clear();

  std::cout << "Energy (J/access): " << interconnect.power.readOp.dynamic << std::endl;
  std::cout << "Area (um^2): " << interconnect.area.get_area() << std::endl;
}
