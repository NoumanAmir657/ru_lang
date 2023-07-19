#ifndef object_h
#define object_h

#include "common.h"
#include "value.h"
#include "chunk.h"
#include "table.h"

// returnz object type
#define OBJ_TYPE(value)     (AS_OBJ(value)->type)

// tells whether an object is string or not
#define IS_BOUND_METHOD(value)  isObjType(value, OBJ_BOUND_METHOD)
#define IS_CLASS(value)         isObjType(value, OBJ_CLASS)
#define IS_CLOSURE(value)       isObjType(value, OBJ_CLOSURE)
#define IS_FUNCTION(value)      isObjType(value, OBJ_FUNCTION)
#define IS_INSTANCE(value)      isObjType(value, OBJ_INSTANCE)
#define IS_NATIVE(value)        isObjType(value, OBJ_NATIVE)
#define IS_STRING(value)        isObjType(value, OBJ_STRING)

// returns ObjBoundMethod
#define AS_BOUND_METHOD(value)  ((ObjBoundMethod*)AS_OBJ(value))
// returns ObjClass
#define AS_CLASS(value)         ((ObjClass*)AS_OBJ(value))
// returns ObjClosure
#define AS_CLOSURE(value)       ((ObjClosure*)AS_OBJ(value))
// returns ObjString
#define AS_STRING(value)        ((ObjString*)AS_OBJ(value))
// returns ObjFunction
#define AS_FUNCTION(value)      ((ObjFunction*)AS_OBJ(value))
// returns ObjString->chars
#define AS_CSTRING(value)       (((ObjString*)AS_OBJ(value))->chars)
// returns native function
#define AS_NATIVE(value)        (((ObjNative*)AS_OBJ(value))->function)
// returns instance
#define AS_INSTANCE(value)((ObjInstance*)AS_OBJ(value))

// enum for object types
typedef enum {
    OBJ_BOUND_METHOD,
    OBJ_CLASS,
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_INSTANCE,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE,
} ObjType;

// object struct contains ObjectType
struct Obj {
    ObjType type;
    struct Obj* next;
    bool isMarked;
};

typedef struct {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString* name;
} ObjFunction;

typedef Value (*NativeFn)(int argCount, Value* args);

typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;

struct ObjString {
    Obj obj;        // base object
    int length;     // length of string
    char* chars;    // actual chars of string
    uint32_t hash;   // hash value of string
};

typedef struct ObjUpvalue {
    Obj obj;
    Value* location;
    Value closed;

    struct ObjUpvalue* next;
} ObjUpvalue;

typedef struct {
    Obj obj;
    ObjFunction* function;

    ObjUpvalue** upvalues;
    int upvalueCount;
} ObjClosure;

typedef struct {
    Obj obj;
    ObjString* name;
    Table methods;
} ObjClass;

typedef struct {
    Obj obj;
    ObjClass* klass;
    Table fields;
} ObjInstance;

typedef struct {
    Obj obj;
    Value receiver;
    ObjClosure* method;
} ObjBoundMethod;

ObjBoundMethod* newBoundMethod(Value receiver, ObjClosure* method);
ObjClass* newClass(ObjString* name);
ObjClosure* newClosure(ObjFunction* function);

// new function
ObjFunction* newFunction();
// new instance
ObjInstance* newInstance(ObjClass* klass);

ObjNative* newNative(NativeFn function);

ObjUpvalue* newUpvalue(Value* slot);

// creates string
ObjString* copyString(const char* chars, int length);
ObjString* takeString(char* chars, int length);

// prints object contents
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif