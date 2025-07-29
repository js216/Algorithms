! 10. Implement Euclid's algorithm in FORTRAN or BASIC.

program read_pairs
   implicit none
   integer :: a, b
   integer :: ios

   do
      read(*, *, iostat=ios) a, b
      if (ios /= 0) exit
      print *, 'GCD:', gcd(a, b)
   end do

contains

function gcd(uin, vin)
    integer :: gcd
    integer, intent(in) :: uin, vin
    integer :: t, u, v

    u = uin
    v = vin

    do while (u > 0)
      if (u < v) then
         t = u
         u = v
         v = t
      end if
      u = u-v
   end do

   gcd = v
end function gcd

end program read_pairs
