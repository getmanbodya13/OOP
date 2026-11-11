#pragma once
class Equation {
protected:
    double a, b;
public:
    Equation(double a, double b);
    virtual ~Equation();
    
    virtual int koreni_rivnyannya(double& x1, double& x2) const = 0;

    virtual void show() const = 0;
};

class LinearEquation : public Equation {
public:
    LinearEquation(double a, double b);
    int koreni_rivnyannya(double& x1, double& x2) const override;
    void show() const override;
};

class QuadraticEquation : public Equation {
    double c;
public:
    QuadraticEquation(double a, double b, double c);
    int koreni_rivnyannya(double& x1, double& x2) const override;
    void show() const override;
};