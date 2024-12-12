#include "FooManager.h"

FooManager* FooManager :: m_Inst = 0;

FooManager :: FooManager() :SampleData(100) {
}
FooManager ::~ FooManager () {

}