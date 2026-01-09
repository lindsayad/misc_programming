#include <Kokkos_Core.hpp>
#include <Kokkos_DualView.hpp>

namespace MetaPhysicL
{

// 1) Public device/host getter with no arguments
struct DoDeriv
{
  using ExecSpace = Kokkos::DefaultExecutionSpace;
  using DevMem = typename ExecSpace::memory_space;

  // Static shallow handle (no ownership)
  static Kokkos::View<const bool, DevMem> s_dflag;

  KOKKOS_INLINE_FUNCTION
  static bool get()
  {
    // rank-0 view access; valid on device & host if DevMem is host-accessible
    return s_dflag();
  }
};

// 2) Host-side owner of the allocation (lives between initialize/finalize)
struct DoDerivHost
{
  static Kokkos::DualView<bool> s_flag; // length-1
};

// 3) Host-side setup/update APIs
inline void
configure_do_derivatives(bool value)
{
  DoDerivHost::s_flag = Kokkos::DualView<bool>("do_derivatives", 1);
  Kokkos::deep_copy(DoDerivHost::s_flag.view_host(), value);
  DoDerivHost::s_flag.modify<Kokkos::HostSpace>();
  DoDerivHost::s_flag.sync<DoDeriv::ExecSpace>();
  DoDeriv::s_dflag = DoDerivHost::s_flag.view_device();
}

inline void
set_do_derivatives(bool value)
{
  Kokkos::deep_copy(DoDerivHost::s_flag.view_host(), value);
  DoDerivHost::s_flag.modify<Kokkos::HostSpace>();
  DoDerivHost::s_flag.sync<DoDeriv::ExecSpace>();
}

// Optional: if device writes the flag, call this before reading on host:
inline void
pull_do_derivatives_to_host()
{
  DoDerivHost::s_flag.modify<DoDeriv::ExecSpace>();
  DoDerivHost::s_flag.sync<Kokkos::HostSpace>();
}

Kokkos::View<const bool, DoDeriv::DevMem> DoDeriv::s_dflag;
Kokkos::DualView<bool> DoDerivHost::s_flag;

} // namespace MetaPhysicL

int
main(int argc, char ** argv)
{
  Kokkos::initialize(argc, argv);
  {
    MetaPhysicL::configure_do_derivatives(/* initial value */ true);

    Kokkos::parallel_for(
        "kernel", 100, KOKKOS_LAMBDA(const int i) {
          if (MetaPhysicL::DoDeriv::get())
          {
            // do derivative work
          }
          else
          {
            // skip
          }
        });

    // Flip at runtime if needed
    MetaPhysicL::set_do_derivatives(false);

    Kokkos::parallel_for(
        "kernel2", 100, KOKKOS_LAMBDA(const int i) {
          if (MetaPhysicL::DoDeriv::get())
          { /* ... */
          }
        });
  }
  Kokkos::finalize();
}
