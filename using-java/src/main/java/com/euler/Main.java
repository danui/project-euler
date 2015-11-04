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
            long t0 = System.currentTimeMillis();
            String result = problem.call();
            long t1 = System.currentTimeMillis();
            System.out.format(
                "Problem %s completed in %d milliseconds. Answer is %s%n",
                name, t1-t0, result);
        }
    }

}
