# Basic CI/CD

Development of a simple **CI/CD** for the *SimpleBashUtils* project. Building, testing, deployment.

The russian version of the task can be found in the repository.

## Part 1. Setting up the **gitlab-runner**

##### Start *Ubuntu Server 22.04 LTS* virtual machine.

##### Download and install **gitlab-runner** on the virtual machine.

##### Run **gitlab-runner** and register it for use in the current project (*DO6_CICD*).
- You will need a URL and a token for runner registration, that can be obtained from the task page on the platform.

## Part 2. Building

#### Write a stage for **CI** to build applications from the *C2_SimpleBashUtils* project.

##### In the _gitlab-ci.yml_ file, add a stage to start the building via makefile from the _C2_ project.

##### Save post-build files (artifacts) to a random directory with a 30-day retention period.


## Part 3. Codestyle test

#### Write a stage for **CI** that runs a codestyle script (*clang-format*).

##### If the codefile didn't pass, "fail" the pipeline.

##### In the pipeline, display the output of the *clang-format* utility.

## Part 4. Integration tests

#### Write a stage for **CI** that runs your integration tests from the same project.

##### Run this stage automatically only if the build and codestyle test passes successfully.

##### If tests didn't pass, "fail" the pipeline.

##### In the pipeline, display the output of the succeeded / failed integration tests.

## Part 5. Deployment stage

##### Start the second virtual machine *Ubuntu Server 22.04 LTS*.

#### Write a stage for **CD** that "deploys" the project on another virtual machine.

##### Run this stage manually, if all the previous stages have passed successfully.

##### Write a bash script which copies the files received after the building (artifacts) into the */usr/local/bin* directory of the second virtual machine using **ssh** and **scp**.

##### In the _gitlab-ci.yml_ file, add a stage to run the script you have written.

##### In case of an error, fail the pipeline.

## Part 6. Bonus. Notifications

**== Task ==**

##### Set up notifications of successful/unsuccessful pipeline execution via bot named "[your nickname] DO6 CI/CD" in *Telegram*.
