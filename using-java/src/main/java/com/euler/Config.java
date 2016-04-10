package com.euler;

import java.util.Map;
import java.util.TreeMap;

public class Config {

    private final String[] args;

    public Config(String[] args) {
        this.args = args;
    }

    public Map<String,Problem> getProblems() {
        Map<String,Problem> result = new TreeMap<>();
        for (int i = 0; i < args.length; ++i) {
            String key = args[i];
            result.put(key, loadProblem(key));
        }
        return result;
    }

    private Problem loadProblem(String key) {
        try {
            String classPath = "com.euler.Problem" + key;
            Class cls = Class.forName(classPath);
            Object obj = cls.newInstance();
            return (Problem)obj;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
