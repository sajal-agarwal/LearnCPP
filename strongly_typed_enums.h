class StronglyTypedEnums {
public:
    enum Color : unsigned long long {   //it is possible to define underlying type for old enums as well
                                        //it is an improvement taken from new enums implementation
        RED,
        GREEN,
        YELLOW
    };

    enum Alert {    //size of old enum auto adujust depending upon its content
                    //its minimum value is size of int, if the underlying list
                    //grows beyond integer, the size of enum increses, basically
                    //the underlying type changes. For example in below scenerio
                    //the size of the enum is = size of long long as the value
                    //for AL_YELLOW is 0xFFFFFFFF+1, which 1 beyound max unsigned
                    //int limit Note: size of an empty enum is = size of int
#if 0
        RED,    //error redeclaration of 'RED' [as there enums are not scoped]
#endif
        AL_RED,
        AL_GREEN = 0xFFFFFFFF,   //enumerators
        AL_YELLOW
    };

    enum class StrongColor : char {   //it is possible to specify underlying type
        RED,                          //default is int, auto can not be used here
        GREEN,
#if 0
        YELLOW = 0x7F,  //not OK as it make BLUE go out of the range
                        //error: enumerator value 128 is outside the range of underlying type 'char'
#endif
#if 1
        YELLOW = 0x7E,
#endif
        BLUE,
#if 0
        PINK = 0xFFF    //not OK, out of range
#endif
    };

    enum class StrongAlert : unsigned char {
        RED,    //OK to reuse the same name
        GREEN,
        YELLOW,
    };

    //Since new enum it is possible to forward declare an enum
    //it is no longer needed to include the header file itself
    //which would result in re-compilation of the file as well
    //below are some examples of forward declared enums:

#if 0
    enum E : short;   //OK: unscoped, underlying type is short
    enum F;     //illegal enum base is required
    enum class H;   //OK: scoped, underlying type is int
    enum class G : short;   //OK: scoped, underlying type is short
#endif
};


#if 0
int main(int /*argc*/, char** /*argv*/) {
#if 0
    StronglyTypedEnums::Color color = 2;    // error: invalid conversion from 'int' to 'StronglyTypedEnums::Color' [-fpermissive]
    StronglyTypedEnums::StrongColor scolor = 3;    // error: cannot convert 'int' to 'StronglyTypedEnums::StrongColor' in initialization]
#endif
    StronglyTypedEnums::Color color = static_cast<StronglyTypedEnums::Color>(2);    //OK, even if value is more than 2
    StronglyTypedEnums::StrongColor scolor = static_cast<StronglyTypedEnums::StrongColor>(3);   //OK, even if value is more than 3



    StronglyTypedEnums::Color color1 = StronglyTypedEnums::RED; // OK with old enums
#if 0
    StronglyTypedEnums::StrongColor scolor1 = StronglyTypedEnums::BLUE; //eror: 'BLUE' is not a member of 'StronglyTypedEnums'
#endif
    StronglyTypedEnums::StrongColor scolor1 = StronglyTypedEnums::StrongColor::BLUE;    // new enums are welled scoped

    bool isValidColor = color1 < 3; //OK with old enums
#if 0
    isValidColor = scolor1 < 4; //error: no match for 'operator<' (operand types are 'StronglyTypedEnums::StrongColor' and 'int')
                                //implicit conversion from int to new enum not supprorted
#endif
    isValidColor = scolor1 < static_cast<StronglyTypedEnums::StrongColor>(5);   //OK



#if 0
    color1 = StronglyTypedEnums::Alert::RED;    //error: 'RED' is not a member of 'StronglyTypedEnums::Alert'
                                                //same is true for new enums
#endif

    std::cout << sizeof(StronglyTypedEnums::Alert) << std::endl;    //2
    std::cout << sizeof(StronglyTypedEnums::StrongAlert) << std::endl;      //8 NOT 4 because one of the value goes beyond the range of
                                                                            //of integer
}
#endif
