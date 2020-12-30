<img src="other/res/logoH.png?raw=true" width="25%">

# HSGIL - Handy Scalable Graphics Integration Library
---

## What is HSGIL?

HSGIL is an OpenSource Graphics Library written in C++ designed for a simple and handy graphics rendering. It's constantly developing and updating to improve its mechanics and features. This is also aimed at the development of the Spectrum Game Engine.

## Test & Analysis instructions
---
To do this process, you may follow these steps:

1. Install Jenkins and deploy it at localhost.
2. Integrate SonarQube with Jenkins.
3. Check if SonarQube has been successfully integrated (look a the 2 following pictures):

<img src="other/res/test/1.jpg?raw=true" width="75%"><br>

<img src="other/res/test/2.jpg?raw=true" width="75%"><br>

4. Go to Administrar Jenkins / System Configuration (Spanish installation):

<img src="other/res/test/3.jpg?raw=true" width="75%"><br>

5. Create the SonarQube server:

<img src="other/res/test/4.jpg?raw=true" width="75%"><br>

6. At Global Tool Configuration, add a Sonnar Scanner:

<img src="other/res/test/5.jpg?raw=true" width="75%"><br>

7. Now, it's time to configure the Pipeline:
```
pipeline {
    agent any

    stages {
        stage('clonacion') {
            steps {
                git 'https://github.com/AsulconS/HSGIL.git'

            }
        }
        stage('construccion') {
            steps {
                sh 'sudo make'
            }
        }

        stage('construccion 2') {
            steps {
                sh 'sudo make finn'
            }
        }
        stage('SonarQube analysis') {
            steps{  
                sh "pwd"
                sh "ls"
                script{
                    def scannerHome = tool 'SonarQube Scanner';
                    withSonarQubeEnv('Sonar') { // If you have configured more than one global server connection, you can specify its name
                        sh "${scannerHome}/bin/sonar-scanner -Dsonar.projectKey=HSGIL-sonar -Dsonar.sources=./src -Dsonar.language=c++"
                    }
                }
            }
        }
        stage('Tests'){
            steps{
                sh "sudo make test"
                sh "./run_unit_tests"
                sh "./run_functional_tests"
            }
        }
    }
}
```

8. Then, we can run the pipeline and check for the results at each stage:

<img src="other/res/test/6.jpg?raw=true" width="75%"><br>

9. Here we are the SonarQube's Results:

<img src="other/res/test/7.jpg?raw=true" width="75%"><br>

<img src="other/res/test/8.jpg?raw=true" width="75%"><br>
