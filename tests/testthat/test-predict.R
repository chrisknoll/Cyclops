library("testthat")
library("ff")
#options(fftempdir = "s:/FFtemp")

test_that("Test predict for Poisson regression", {
    sim <- simulateCyclopsData(nstrata = 1, nrows = 10000, ncovars = 2, eCovarsPerRow = 0.5, effectSizeSd = 1,model = "poisson")
    covariates <- sim$covariates
    outcomes <- sim$outcomes

    cyclopsData <- convertToCyclopsData(outcomes, covariates, modelType = "pr", addIntercept = TRUE)
    fit <- fitCyclopsModel(cyclopsData, prior = createPrior("none"))
    predictOriginal <- predict(fit)

    # Test using data frames
    predictNew <- predict(fit, outcomes, covariates)
    expect_lt(max(abs(predictOriginal - predictNew)), 1e-08)

    # Test using ffdf
    predictNew <- predict(fit, as.ffdf(outcomes),as.ffdf(covariates))
    expect_lt(max(abs(predictOriginal - predictNew)), 1e-08)
})

test_that("Test predict for logistic regression", {
    sim <- simulateCyclopsData(nstrata = 1, nrows = 10000, ncovars = 2, eCovarsPerRow = 0.5, effectSizeSd = 1,model = "logistic")
    covariates <- sim$covariates
    outcomes <- sim$outcomes

    cyclopsData <- convertToCyclopsData(outcomes, covariates, modelType = "lr", addIntercept = TRUE)
    fit <- fitCyclopsModel(cyclopsData, prior = createPrior("none"))
    predictOriginal <- predict(fit)

    # Test using data frames
    predictNew <- predict(fit, outcomes, covariates)
    expect_lt(max(abs(predictOriginal - predictNew)), 1e-08)

    # Test using ffdf
    predictNew <- predict(fit, as.ffdf(outcomes),as.ffdf(covariates))
    expect_lt(max(abs(predictOriginal - predictNew)), 1e-08)
})