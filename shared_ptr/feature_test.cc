#include  <iostream>
#include  <memory>

//TODO: 1. how to represent a null shared_ptr                            : see example in main
//      2. how to check a share_ptr is  exsited                          : see example in main
//      3. how to check the shared object is exsited                     : You can't do it if you fetch a raw pointer from shared_ptr and then destroy it
//      4. how to get the shared_ptr counter                             : see example in main 
//      5. Will shared_ptr be increased counter after return it as value : g++ No
//      6. how to get raw pointer from shared_ptr                        : get method
//      7. how to customize the destroy method                           : see example in main
//
struct Foo {
    int member;
    Foo():member(256) { std::cout << "Foo...\n"; }
    void dosomething(){ std::cout << "Foo do something..."<< member<<"\n"; }
    ~Foo() { std::cout << "~Foo...\n"; }
};
 
struct D { 
    void operator()(Foo* p) const {
        std::cout << "Call delete for Foo object...\n";
        delete p;
    }
};
typedef std::shared_ptr<Foo> Foo_share_p_t;
typedef const std::shared_ptr<Foo>& Foo_share_pc_t;

//NOTE:using a simple way declaration instead of std::shared_ptr<Foo> 
Foo_share_p_t ext_constructor()
{
     Foo_share_p_t sh(new Foo);
     std::cout << "sh in ext_constructor is null: "<<!sh << '\n';
     std::cout << "sh in ext_constructor use count" <<sh.use_count() << '\n';
     return sh;
}

void test_pass_by_const_ref(Foo_share_pc_t ptr)
{

     std::cout << "const ptr reference in ext_constructor is null: "<<!ptr << '\n';
     std::cout << "const ptr reference in ext_constructor use count" <<ptr.use_count() << '\n';
}

int main()
{
    {
        // 1 , 2, 4
        std::cout << "constructor with no managed object\n";
        Foo_share_p_t sh1;
        std::cout << sh1.use_count() << '\n';
        std::cout << "is null: "<<!sh1 << '\n';
    }
 
    {
        //2
        std::cout << "constructor with object\n";
        Foo_share_p_t sh2(new Foo);
        std::cout << "sh2 is null: "<<!sh2 << '\n';
        std::cout << "sh2 use count" <<sh2.use_count() << '\n';
        Foo_share_p_t sh3(sh2);
        std::cout << "sh2 is null: "<<!sh2 << '\n';
        std::cout << "sh2 use count" <<sh2.use_count() << '\n';
        std::cout << "sh3 is null: "<<!sh3 << '\n';
        std::cout << "sh3 use count" <<sh3.use_count() << '\n';
        Foo_share_p_t sh4 = sh2;
        std::cout << "sh2 is null: "<<!sh2 << '\n';
        std::cout << "sh2 use count" <<sh2.use_count() << '\n';
        std::cout << "sh3 is null: "<<!sh3 << '\n';
        std::cout << "sh3 use count" <<sh3.use_count() << '\n';
        std::cout << "sh4 is null: "<<!sh4 << '\n';
        std::cout << "sh4 use count" <<sh4.use_count() << '\n';
        sh2->dosomething();
    }
 
    {
        //7
        std::cout << "constructor with object and deleter\n";
        Foo_share_p_t sh5(new Foo, D());
    }
    {
        //5
        std::cout << "constructor using factory\n";
        Foo_share_p_t sh6 = ext_constructor();
        std::cout << "sh6 is null: "<<!sh6 << '\n';
        std::cout << "sh6 use count" <<sh6.use_count() << '\n';
        test_pass_by_const_ref(sh6);
        std::cout << "call sh6.reset(new Foo)\n";
        sh6.reset( new Foo);
        std::cout << "sh6 is null: "<<!sh6 << '\n';
        std::cout << "sh6 use count" <<sh6.use_count() << '\n';
        std::cout << "call sh6.reset()\n";
        sh6.reset();
        std::cout << "sh6 is null: "<<!sh6 << '\n';
        std::cout << "sh6 use count" <<sh6.use_count() << '\n';

    }
    {
        //3, 6
        std::cout << "constructor with object\n";
        Foo_share_p_t sh7 (new Foo);
        std::cout << "sh7 is null: "<<!sh7 << '\n';
        std::cout << "sh7 use count" <<sh7.use_count() << '\n';
        Foo * foo = sh7.get();
        foo->dosomething();
        //{
        //FIXME: what a terrible thing!!!!!!!!!!!!!
        //delete foo; 
        //foo->dosomething();
        //}
        std::cout << "sh7 is null: "<<!sh7 << '\n';
        std::cout << "sh7 use count" <<sh7.use_count() << '\n';
        sh7->dosomething();
    }
}

