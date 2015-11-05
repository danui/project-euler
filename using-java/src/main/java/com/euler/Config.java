package com.euler;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class Config {

    private static interface ProblemLoader {
        public Problem load();
    }

    private static final Map<String,ProblemLoader> LOADERS = new HashMap<>();
    {
        // TODO This is a pain to maintain. Can we use ClassLoader magic?
        LOADERS.put("24", new ProblemLoader() {
            @Override
            public Problem load() {
                return new Problem24();
            }
        });
        LOADERS.put("27", new ProblemLoader() {
            @Override
            public Problem load() {
                return new Problem27();
            }
        });
        LOADERS.put("28", new ProblemLoader() {
            @Override
            public Problem load() {
                return new Problem28();
            }
        });
    }

    private static Problem loadProblem(String key) {
        ProblemLoader loader = LOADERS.get(key);
        if (loader == null) {
            // TODO Print a list of known problems then.
            throw new IllegalArgumentException(
                "Not a known problem: "+key);
        }
        return loader.load();
    }

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

}
