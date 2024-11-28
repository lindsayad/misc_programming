#include <netcdf.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

#define NC_CHECK(err)                                                                              \
  {                                                                                                \
    if (err != NC_NOERR)                                                                           \
    {                                                                                              \
      std::cerr << "NetCDF error: " << nc_strerror(err) << std::endl;                              \
      return err;                                                                                  \
    }                                                                                              \
  }

int
main()
{
  int ncid, varid, block_id_varid;
  size_t num_blocks;

  // Open the NetCDF file (read-only)
  NC_CHECK(nc_open("example.exo", NC_NOWRITE, &ncid));

  // Find the dimension ID for "num_el_blk"
  int dimid;
  NC_CHECK(nc_inq_dimid(ncid, "num_el_blk", &dimid));

  // Get the number of element blocks
  NC_CHECK(nc_inq_dimlen(ncid, dimid, &num_blocks));

  // Retrieve the block IDs
  std::vector<int> block_ids(num_blocks);
  NC_CHECK(nc_inq_varid(ncid, "eb_prop1", &block_id_varid));
  NC_CHECK(nc_get_var_int(ncid, block_id_varid, block_ids.data()));

  // Find the variable ID for "eb_names" which stores element block names
  NC_CHECK(nc_inq_varid(ncid, "eb_names", &varid));

  // Create a map from block ID to block name
  std::unordered_map<int, std::string> block_map;

  // Iterate over the block IDs and retrieve the corresponding block names
  size_t start[1], count[1];
  count[0] = 1;
  char block_name[NC_MAX_NAME + 1]; // Buffer to hold block name temporarily

  for (size_t i = 0; i < num_blocks; i++)
  {
    start[0] = i;
    NC_CHECK(nc_get_vara_text(ncid, varid, start, count, block_name));

    // Ensure null-termination of the string
    block_name[NC_MAX_NAME] = '\0';

    // Store the block ID and name in the map
    block_map[block_ids[i]] = std::string(block_name);
  }

  // Print the map
  for (const auto & pair : block_map)
  {
    std::cout << "Block ID: " << pair.first << ", Block Name: " << pair.second << std::endl;
  }

  // Close the NetCDF file
  NC_CHECK(nc_close(ncid));

  return 0;
}
