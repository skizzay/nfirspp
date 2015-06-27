#language: en

Feature: Tags
  In order to be part of a fire department
  I have to be able to create a fire department and add members to it

  Scenario: Registering a fire department
    Given I have a fire department
    When I register the fire department 15055-NJ
    Then the fire department should be registered
