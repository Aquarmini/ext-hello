<?php
// +----------------------------------------------------------------------
// | BaseTest.php [ WE CAN DO IT JUST THINK IT ]
// +----------------------------------------------------------------------
// | Copyright (c) 2016-2017 limingxinleo All rights reserved.
// +----------------------------------------------------------------------
// | Author: limx <715557344@qq.com> <https://github.com/limingxinleo>
// +----------------------------------------------------------------------
namespace Tests\Test;

use Tests\TestCase;
use Hello;

class BaseTest extends TestCase
{
    public function testExample()
    {
        $this->assertTrue(true);
    }

    public function testRTrue()
    {
        $obj = new Hello();
        $this->assertTrue($obj->rTrue());
    }

    public function testRInt()
    {
        $obj = new Hello();
        $this->assertTrue($obj->rInt() === 11521);
    }

    public function testRString()
    {
        $obj = new Hello();
        $this->assertTrue($obj->rString() === 'hello world!');
    }

    public function testHi()
    {
        $obj = new Hello();
        $this->assertTrue($obj->hi('limx') === 'hi, limx!');
    }
}
