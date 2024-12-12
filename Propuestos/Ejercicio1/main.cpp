#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <ctime>

enum class TipoCuenta {
    AHORRO,
    JOVEN,
    PLUSS,
    EMPRESARIAL,
    TARJETA_CREDITO
};


template<typename T>
class RepositorioSingleton {
protected:
    RepositorioSingleton() = default;

    static T* instancia;

public:
    static T* obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new T();
        }
        return instancia;
    }

    virtual ~RepositorioSingleton() = default;
    RepositorioSingleton(const RepositorioSingleton&) = delete;
    RepositorioSingleton& operator=(const RepositorioSingleton&) = delete;
};

template<typename T>
T* RepositorioSingleton<T>::instancia = nullptr;

class RepositorioCuentas : public RepositorioSingleton<RepositorioCuentas> {
private:
    // Mapa para almacenar cuentas de clientes
    std::unordered_map<std::string, std::vector<TipoCuenta>> cuentasClientes;
    
    // Tasas de interés por tipo de cuenta
    std::unordered_map<TipoCuenta, float> tasasInteres = {
        {TipoCuenta::AHORRO, 0.5f},
        {TipoCuenta::JOVEN, 1.0f},
        {TipoCuenta::PLUSS, 2.0f},
        {TipoCuenta::EMPRESARIAL, 4.0f},
        {TipoCuenta::TARJETA_CREDITO, 25.0f}
    };
    friend class RepositorioSingleton<RepositorioCuentas>;
    RepositorioCuentas() = default;

public:
    // Registrar nueva cuenta para un cliente
    void registrarCuenta(const std::string& nombreCliente, TipoCuenta tipoCuenta) {
        cuentasClientes[nombreCliente].push_back(tipoCuenta);
    }

    // Calcular interés para un tipo de cuenta
    float calcularInteres(TipoCuenta tipoCuenta) {
        return tasasInteres[tipoCuenta];
    }

    // Generar estado de cuenta
    void generarEstadoCuenta(const std::string& nombreCliente, time_t fechaCorte) {
        std::cout << "---------------------------------" << std::endl;
        std::cout << "Estado de cuenta para: " << nombreCliente << std::endl;
        std::cout << "Fecha de corte: " << std::ctime(&fechaCorte);
        
        for (auto tipoCuenta : cuentasClientes[nombreCliente]) {
            std::cout << "Tipo de cuenta: " 
                      << static_cast<int>(tipoCuenta) 
                      << ", Tasa de interés: " 
                      << calcularInteres(tipoCuenta) << "%" << std::endl;
        }
    }
};

int main() {
    auto repositorio = RepositorioCuentas::obtenerInstancia();

    // Registrar cuentas para clientes
    repositorio->registrarCuenta("Juan Perez", TipoCuenta::AHORRO);
    repositorio->registrarCuenta("Juan Perez", TipoCuenta::TARJETA_CREDITO);
    repositorio->registrarCuenta("Maria Garcia", TipoCuenta::EMPRESARIAL);

    // Generar estado de cuenta
    time_t fechaCorte = time(nullptr);
    repositorio->generarEstadoCuenta("Juan Perez", fechaCorte);
    repositorio->generarEstadoCuenta("Maria Garcia", fechaCorte);

    return 0;
}