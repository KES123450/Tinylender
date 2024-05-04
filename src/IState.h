
class IState{
    virtual ~IState() {};
    virtual void Handle() =0;
}