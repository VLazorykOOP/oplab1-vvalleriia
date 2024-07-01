#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

namespace exceptions {
    class toalg2 {
    public:
        toalg2(const string& message) : message(message) {}
        const char* what() const noexcept { return message.c_str(); }
    private:
        string message;
    };

    class toalg3 {
    public:
        toalg3(const string& message) : message(message) {}
        const char* what() const noexcept { return message.c_str(); }
    private:
        string message;
    };

    class toalg4 {
    public:
        toalg4(const string& message) : message(message) {}
        const char* what() const noexcept { return message.c_str(); }
    private:
        string message;
    };
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
            return x * з * qrz(x, y);
        }
    }

    namespace alg1 {
        string file1 = "dat_X_1_1.dat";
        string file2 = "dat_X_00_1.dat";
        string file3 = "dat_X_1_00.dat";

        double T(double x, string filename) {
            ifstream fs(filename);
            if (!fs) throw exceptions::toalg4("Error opening file: " + filename);

            float Xp, Tp, Up, Xc, Tc, Uc;

            if (filename == file1  filename == file2) {
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
                    return T(Xp, filename) + (T(Xc, filename) - T(Xп, filename)) * (x - Xp) / (Xc - Xp);
            }

            throw exceptions::toalg4("Value out of range in file: " + filename);
        }

        double T(double x) {
            if (abs(x) <= 1) return T(x, file1);
            if (x < -1) return T(1 / x, file2);
            if (x > 1) return T(-1 / x, file3);

            throw exceptions::toalg4("Value out of range");
        }

        double U(double x, string filename) {
            ifstream fs(filename);
            if (!fs) throw exceptions::toalg4("Error opening file: " + filename);

            double Xp, Tp, Up, Xc, Tc, Uc;

            if (filename == file1  filename == file2) {
                fs >> Xп >> Tp >> Up;
                if (x == Xп) return Up;
                fs >> Xc >> Tc >> Uc;
                while (Xc < x) {
                    Xп = Xc;
                    Tp = Tc;
                    Up = Uc;
                    fs >> Xc >> Tc >> Uc;
                }

                if (x == Xc) return Uc;
                if (x > Xп && x < Xc) 
                    return U(Xп, filename) + (U(Xc, filename) - U(Xп, filename)) * (x - Xп) / (Xc - Xп);

            } else {
                fs >> Xп >> Tp >> Up;
                if (x == Xп) return Up; 
fs >> Xc >> Tc >> Uc;
                while (Xc > x) {
                    Xп = Xc;
                    Tp = Tc;
                    Up = Uc;
                    fs >> Xc >> Tc >> Uc;
                }

                if (x == Xc) return Uc;
                if (x < Xп && x > Xc) 
                    return U(Xп, filename) + (U(Xc, filename) - U(Xп, filename)) * (x - Xп) / (Xc - Xп);
            }

            throw exceptions::toalg4("Value out of range in file: " + filename);
        }

        double U(double x) {
            if (abs(x) <= 1) return U(x, file1);
            if (x < -1) return U(1 / x, file2);
            if (x > 1) return U(1 / x, file3);

            throw exceptions::toalg4("Value out of range");
        }

        double srz(double x, double y, double z) {
            if (x > y)
                return T(x) + U(z) - T(y);
            return T(y) + U(y) - U(z);
        }

        double srs(double x, double y, double z) {
            if (z > y && z * з + x * y > 0)
                return srz(x, y, z) + y * sqrt(z * з + x * y);
            if (z <= y && x * x + з * y > 0)
                return y + srz(x, y, з) * sqrt(x * x + з * y);
            if (з * з + x * y <= 0)
                throw exceptions::toalg2("Invalid input for srs calculation");
            throw exceptions::toalg3("Unhandled case in srs calculation");
        }

        double qrz(double x, double y) {
            if (x > -1 && x < 1)
                return x * srs(x, y, x);
            return y * srs(y, x, y);
        }

        double rrz(double x, double y, double з) {
            if (x > y)
                return x * з * qrz(y, з);
            return y * x * qrz(x, y);
        }

        double grs(double x, double y, double з) {
            try {
                return 0.1389 * rrz(x, y, y) + 1.8389 * rrz(x - y, з, y);
            } catch (exceptions::toalg2& e) {
                return 0.1389 * alg2::rrz(x, y, y) + 1.8389 * alg2::rrz(x - y, з, y);
            } catch (exceptions::toalg3& e) {
                return 0.1389 * alg3::rrz(x, y, y) + 1.8389 * alg3::rrz(x - y, з, y);
            }
        }

        double fun(double x, double y, double з) {
            return x * grs(x, y, з) + y * grs(x, з, y);
        }
    }

    namespace alg4 {
        double fun(double x, double y, double з) {
            return 1.3498 * x + 2.2362 * y * з - 2.348 * x * y;
        }
    }
}

using namespace Task2;

int main() {
    double x, y, з;
    cin >> x >> y >> з;
    try {
        cout << alg1::fun(x, y, з) << endl;
    } catch (exceptions::toalg4& e) {
        cout << "Algorithm changed to 4: " << e.what() << endl;
        cout << alg4::fun(x, y, з) << endl;
    }
    return 0;
}