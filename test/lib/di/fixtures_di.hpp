struct IFirst
{
  virtual int run() = 0;
};

struct ISecond
{
  virtual double run() = 0;
};

class First : public IFirst
{
  public:
    First() : val(0) { ; }
    First(int value) : val(value) { ; }
    int run() { return val; }

  private:
    int val;
};

class Second : public ISecond
{
  public:
    Second() : val(0.0) { ; }
    Second(double value) : val(value) { ; }
    double run() { return val; }

  private:
    double val;
};

class UseIFirstISecond
{
  public:
    UseIFirstISecond(IFirst& first, ISecond& second) : first(first), second(second) { ; }
    int first_run() {
      return first.run();
    }

    double second_run() {
      return second.run();
    }

  private:
    IFirst& first;
    ISecond& second;
};

First first_default;
Second second_default;
