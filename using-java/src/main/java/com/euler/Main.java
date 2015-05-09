package com.euler;

import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.Map;

public class Main {

    public static void main(String[] args) throws Exception {
        Config config = new Config(args);
        Map<String,Problem> problems = config.getProblems();
        for (Map.Entry<String,Problem> i : problems.entrySet()) {
            String name = i.getKey();
            Problem problem = i.getValue();
            String result = problem.call();
            System.out.format("Answer for Problem %s is %s%n", name, result);
            // TODO Add timing calls here. Remove them from Problem24. And
            // update the README.md example.
        }
    }

}
