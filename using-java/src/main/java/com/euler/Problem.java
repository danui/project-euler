package com.euler;

import java.util.concurrent.Callable;

public interface Problem {
    public String getName();
    public Callable<String> getTask();
}
