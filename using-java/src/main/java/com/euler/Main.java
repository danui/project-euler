package com.euler;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;

public class Main {

    public static void main(String[] args) throws Exception {
        Config config = new Config(args);
        ExecutorService executor = Executors.newCachedThreadPool();
        for (Problem i : config.getProblems()) {
            String name = i.getName();
            Callable<String> task = i.getTask();
            Future<String> pending = executor.submit(task);
            String result = pending.get();
            System.out.format("Answer for Problem %s is %s%n", name, result);
            // TODO Add timing calls here. Remove them from Problem24. And
            // update the README.md example.
        }
        executor.shutdownNow();
    }

}
