#include "hdf5.h"
#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define CHKERR(handle)                                                         \
  if (handle < 0)                                                              \
  throw std::runtime_error("an hdf5 API didn't work")

class ElementAverageValue {
public:
  ElementAverageValue(
      const std::unordered_map<unsigned int, double> &my_region_to_temp,
      const std::string &file_name, const unsigned int total_num_regions)
      : _my_region_to_temp(my_region_to_temp), _file_name(file_name) {
    if (!_have_file_instance) {
      _file_handle = H5Fcreate(_file_name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT,
                               H5P_DEFAULT);
      if (_file_handle < 0)
        throw std::runtime_error("Failed to create file");
      _have_file_instance = true;

      auto cp_group = H5Gcreate(_file_handle, "cell_properties", H5P_DEFAULT,
                                H5P_DEFAULT, H5P_DEFAULT);
      CHKERR(cp_group);
      auto region_group = H5Gcreate(cp_group, "by_region", H5P_DEFAULT,
                                    H5P_DEFAULT, H5P_DEFAULT);

      hsize_t rank[1] = {total_num_regions};

      _dataspace_handle = H5Screate_simple(1, rank, NULL);

      _datatype_handle = H5Tcopy(H5T_IEEE_F64LE);

      _dataset_handle =
          H5Dcreate(region_group, "temperature", _datatype_handle,
                    _dataspace_handle, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

      H5Sclose(_dataspace_handle);
      H5Tclose(_datatype_handle);
      H5Dclose(_dataset_handle);
      H5Gclose(region_group);
      H5Gclose(cp_group);
      H5Fclose(_file_handle);

      _total_num_regions = total_num_regions;
    }

    if (_total_num_regions != total_num_regions)
      throw std::runtime_error("All instances of ElementAverageValue must have "
                               "the same value for total_num_regions!");
  }

  void writeData() {
    auto file_handle = H5Fopen(_file_name.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
    CHKERR(file_handle);

    auto group = H5Gopen(file_handle, "cell_properties/by_region", H5P_DEFAULT);

    auto dataset_handle = H5Dopen(group, "temperature", H5P_DEFAULT);
    CHKERR(file_handle);

    auto dataspace_handle = H5Dget_space(dataset_handle);
    CHKERR(dataspace_handle);

    hsize_t memspace_dims[1] = {1};
    auto memspace = H5Screate_simple(1, memspace_dims, NULL);
    CHKERR(memspace);

    for (const auto &pr : _my_region_to_temp) {
      auto region = pr.first;
      double temperature[1] = {pr.second};

      hsize_t offset[1] = {region};
      hsize_t count[1] = {1};

      auto status = H5Sselect_hyperslab(dataspace_handle, H5S_SELECT_SET,
                                        offset, NULL, count, NULL);
      CHKERR(status);

      status = H5Dwrite(dataset_handle, H5T_IEEE_F64LE, memspace,
                        dataspace_handle, H5P_DEFAULT, temperature);
      CHKERR(status);
    }

    H5Fclose(file_handle);
    H5Gclose(group);
    H5Dclose(dataset_handle);
    H5Sclose(dataspace_handle);
  }

private:
  static bool _have_file_instance;
  static hid_t _file_handle;
  static hid_t _dataspace_handle;
  static hid_t _datatype_handle;
  static hid_t _dataset_handle;
  static unsigned int _total_num_regions;

  std::unordered_map<unsigned int, double> _my_region_to_temp;
  std::string _file_name;
};

bool ElementAverageValue::_have_file_instance = false;
hid_t ElementAverageValue::_file_handle = 0;
hid_t ElementAverageValue::_dataspace_handle = 0;
hid_t ElementAverageValue::_datatype_handle = 0;
hid_t ElementAverageValue::_dataset_handle = 0;
unsigned int ElementAverageValue::_total_num_regions = 0;

int main() {
  std::vector<ElementAverageValue> emvs = {
      ElementAverageValue({{0, 10.}, {4, 20.}, {8, 30.}}, "temperature.h5", 12),
      ElementAverageValue({{1, 40.}, {5, 50.}, {9, 60.}}, "temperature.h5", 12),
      ElementAverageValue({{2, 70.}, {6, 80.}, {10, 90.}}, "temperature.h5",
                          12),
      ElementAverageValue({{3, 100.}, {7, 110.}, {11, 120.}}, "temperature.h5",
                          12)};

  for (auto &emv : emvs)
    emv.writeData();

  auto file = H5Fopen("temperature.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
  CHKERR(file);

  auto group = H5Gopen(file, "cell_properties/by_region", H5P_DEFAULT);

  auto dataset = H5Dopen(group, "temperature", H5P_DEFAULT);
  CHKERR(file);

  double temperature[12];

  auto status = H5Dread(dataset, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT,
                        temperature);
  CHKERR(status);

  for (unsigned int i = 0; i < 12; ++i)
    std::cout << temperature[i] << std::endl;

  H5Fclose(file);
  H5Gclose(group);
  H5Dclose(dataset);
}
