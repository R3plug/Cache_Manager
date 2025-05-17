#include "../cache_manager.h"
#include <iostream>
#include "gtest/gtest.h"
#include "../dll_node.h"

namespace my {
    namespace project {
    namespace {

    struct CacheManagerTest : public testing::Test{
        CacheManager* testManager;
        int key1 = 20;
        int key2 =30;
        int key3 = 25;
        int key4 = 10;
        int key5= 13;
        int key6 = 26;
        int key7 = 22;
        int key8 = 5;
        int key9 = 1;
        int key10 = 27;
        int key11 = 45;
        DllNode* node1 = new DllNode(key1);
        DllNode* node2 = new DllNode(key2);
        DllNode* node3 = new DllNode(key3);
        DllNode* node4 = new DllNode(key4);
        DllNode* node5 = new DllNode(key5);
        DllNode* node6 = new DllNode(key6);
        DllNode* node7 = new DllNode(key7);
        DllNode* node8 = new DllNode(key8);
        DllNode* node9 = new DllNode(key9);
        DllNode* node10 = new DllNode(key10);
        DllNode* node11 = new DllNode(key11);
        


        virtual void SetUp() override {
            testManager = new CacheManager(10,10);
        }
        virtual void TearDown() override{
            testManager->clear();
        }
    };

    TEST_F(CacheManagerTest, addTest){
        testManager->add(key1,node1);
        ASSERT_EQ(testManager->isEmpty(),false);
        testManager->add(key2,node2);
        testManager->add(key3,node3);
        testManager->add(key4,node4);
        ASSERT_EQ(testManager->getSize(),4);
        testManager->add(key5,node5);
        testManager->add(key6,node6);
        testManager->add(key7,node7);
        testManager->add(key8,node8);
        testManager->add(key9,node9);
        testManager->add(key10,node10);
        ASSERT_EQ(testManager->getSize(),10);
        testManager->add(key11,node11);
        //test if it will pop off end if max size reached
        ASSERT_EQ(testManager->getSize(),10);
        //test that a node that already exists wont be added
        ASSERT_EQ(testManager->add(key5,node5),false);

    }
    TEST_F(CacheManagerTest, removeTest){

        testManager->add(key1,node1);
        testManager->add(key2,node2);
        testManager->add(key3,node3);
        testManager->add(key4,node4);
        testManager->add(key5,node5);
        testManager->add(key6,node6);
        testManager->add(key7,node7);
        testManager->add(key8,node8);
        testManager->add(key9,node9);
        //remove from end
        ASSERT_EQ(testManager->remove(key9), true);
        ASSERT_EQ(testManager->getSize(),8);
        //remove from front
        ASSERT_EQ(testManager->remove(key1), true);
        ASSERT_EQ(testManager->getSize(),7);
        //remove from middle
        ASSERT_EQ(testManager->remove(key5), true);
        ASSERT_EQ(testManager->getSize(),6);
    }
    // test to check that accessed items are moved to the front.
    TEST_F(CacheManagerTest, moveToFrontTest){
        testManager->add(key1,node1);
        testManager->add(key2,node2);
        testManager->add(key3,node3);
        testManager->add(key4,node4);
        testManager->add(key5,node5);
        testManager->add(key6,node6);
        testManager->add(key7,node7);
        testManager->add(key8,node8);
        testManager->add(key9,node9);
        //access key from the middle
        testManager->contains(key5);
        ASSERT_EQ(testManager->getList()->head->key,key5);

        //access key from the back
        testManager->contains(key9);
        ASSERT_EQ(testManager->getList()->head->key,key9);


    }
        
        

}
}
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}