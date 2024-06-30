#include <iostream> 
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>
using namespace std;

namespace exceptions {
    class toalg2 {};
    class toalg3 {};
    class toalg4 {};
}

namespace Task2 {
    namespace alg1 {
        double srz(double x, double y, double z);
    }

    namespace alg3 {
        double srs(double x, double y, double z) {
            if (z > y)
                return alg1::srz(x, y, z) + y * x;
            return alg1::srz(z, x, y) + y * z;
        }

        double qrz(double x, double y) {
            if (x > -1 && x < 1)
                return x * srs(x, y, x);
            return y * srs(y, x, y);
        }

        double rrz(double x, double y, double z) {
            if (x > y)
                return x * y * qrz(y, z);
            return y * z * qrz(x, y);
        }
    }

    namespace alg2 {
        double srs(double x, double y, double z) {
            if (z > y)
                return alg1::srz(x, y, z) + 1.44 * y * z;
            return y + 1.44 * alg1::srz(z, x, y);
        }

        double qrz(double x, double y) {
            if (y > -1 && y < 1)
                return x * srs(x, y, x);
            return y * srs(y, x, y);
        }

        double rrz(double x, double y, double z) {
            if (x > y)
                return x * y * qrz(y, z);
            return x * z * qrz(x, y);
        }
    }

    namespace alg1 {
        string file1 = "dat_X_1_1.dat";
        string file2 = "dat_X_00_1.dat";
        string file3 = "dat_X_1_00.dat";

        double T(double x, string filename) {
            ifstream fs(filename);
            if (!fs) throw exceptions::toalg4();

            float Xp, Tp, Up, Xc, Tc, Uc;

            if (filename == file1 || filename == file2) {
                fs >> Xp >> Tp >> Up;
                if (x == Xp) return Tp;

                fs >> Xc >> Tc >> Uc;
                while (Xc < x) {
                    Xp = Xc;
                    Tp = Tc;
                    Up = Uc;
                    fs >> Xc >> Tc >> Uc;
                }

                if (x == Xc) return Tc;
                if (x > Xp && x < Xc) 
                    return T(Xp, filename) + (T(Xc, filename) - T(Xp, filename)) * (x - Xp) / (Xc - Xp);

            } else {
                fs >> Xp >> Tp >> Up;
                if (x == Xp) return Tp;

                fs >> Xc >> Tc >> Uc;
                while (Xc > x) {
                    Xp = Xc;
                    Tp = Tc;
                    Up = Uc;
                    fs >> Xc >> Tc >> Uc;
                }

                if (x == Xc) return Tc;
                if (x < Xp && x > Xc) 
                    return T(Xp, filename) + (T(Xc, filename) - T(Xp, filename)) * (x - Xp) / (Xc - Xp);
            }

            // Return a default value in case of failure to find a return value
            throw exceptions::toalg4();
        }

        double T(double x) {
            if (abs(x) <= 1) return T(x, file1);
            if (x < -1) return T(1 / x, file2);
            if (x > 1) return T(-1 / x, file3);

            // Return a default value in case of failure to find a return value
            throw exceptions::toalg4();
        }

        double U(double x, string filename) {
            ifstream fs(filename);
            if (!fs) throw exceptions::toalg4();

            double Xp, Tp, Up, Xc, Tc, Uc;

            if (filename == file1 || filename == file2) {
                fs >> Xp >> Tp >> Up;
                if (x == Xp) return Up;

                fs >> Xc >> Tc >> Uc;
                while (Xc < x) {
                    Xp = Xc;
                    Tp = Tc;
                    Up = Uc;
                    fs >> Xc >> Tc >> Uc;
                }

                if (x == Xc) return Uc;
                if (x > Xp && x < Xc) 
                    return U(Xp, filename) + (U(Xc, filename) - U(Xp, filename)) * (x - Xp) / (Xc - Xp);

            } else {
                fs >> Xp >> Tp >> Up;
                if (x == Xp) return Up;

                fs >> Xc >> Tc >> Uc;
                while (Xc > x) {
                    Xp = Xc;
                    Tp = Tc;
                    Up = Uc;
                    fs >> Xc >> Tc >> Uc;
                }

                if (x == Xc) return Uc;
                if (x < Xp && x > Xc) 
                    return U(Xp, filename) + (U(Xc, filename) - U(Xp, filename)) * (x - Xp) / (Xc - Xp);
            }

            // Return a default value in case of failure to find a return value
            throw exceptions::toalg4();
        }

        double U(double x) {
            if (abs(x) <= 1) return U(x, file1);
            if (x < -1) return U(1 / x, file2);
            if (x > 1) return U(1 / x, file3);

            // Return a default value in case of failure to find a return value
            throw exceptions::toalg4();
        }

        double srz(double x, double y, double z) {
            if (x > y)
                return T(x) + U(z) - T(y);
            return T(y) + U(y) - U(z);
        }

        double srs(double x, double y, double z) {
            if (z > y && z * z + x * y > 0)
                return srz(x, y, z) + y * sqrt(z * z + x * y);
            if (z <= y && x * x + z * y > 0)
                return y + srz(x, y, z) * sqrt(x * x + z * y);
            if (z * z + x * y <= 0)
                throw exceptions::toalg2();
            throw exceptions::toalg3();
        }

        double qrz(double x, double y) {
            if (x > -1 && x < 1)
                return x * srs(x, y, x);
            return y * srs(y, x, y);
        }

        double rrz(double x, double y, double z) {
            if (x > y)
                return x * z * qrz(y, z);
            return y * x * qrz(x, y);
        }

        double grs(double x, double y, double z) {
            try {
                return 0.1389 * rrz(x, y, y) + 1.8389 * rrz(x - y, z, y);
            } catch (exceptions::toalg2) {
                return 0.1389 * alg2::rrz(x, y, y) + 1.8389 * alg2::rrz(x - y, z, y);
            } catch (exceptions::toalg3) {
                return 0.1389 * alg3::rrz(x, y, y) + 1.8389 * alg3::rrz(x - y, z, y);
            }
        }

        double fun(double x, double y, double z) {
            return x * grs(x, y, z) + y * grs(x, z, y);
        }
    }

    namespace alg4 {
        double fun(double x, double y, double z) {
            return 1.3498 * x + 2.2362 * y * z - 2.348 * x * y;
        }
    }
}

using namespace Task2;

int main() {
    double x, y, z;
    cin >> x >> y >> z;
    try {
        cout << alg1::fun(x, y, z) << endl;
    } catch (exceptions::toalg4) {
        cout << "Algorithm changed to 4" << endl;
        cout << alg4::fun(x, y, z);
    }
    return 0;
}
