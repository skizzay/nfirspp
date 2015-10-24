#language: en

Feature: Incident Dispatching
  In order to have a fire department respond to an incident
  I have to be able to dispatch the fire department

  Scenario Outline: Dispatching a fire department
    Given I have an incident '99e51168-950b-41b5-a346-f875d42af5f5'
    When I dispatch the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' as <dispatch_type> response
    Then the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' should have been <dispatch_type> dispatched
    Examples:
      | dispatch_type |
      | primary       |
      | automatic     |
      | requested     |
      | other         |


  Scenario Outline: Correcting the dispatch
    Given I have an incident '99e51168-950b-41b5-a346-f875d42af5f5'
    When I dispatch the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' as <first_dispatch_type> response
    And I dispatch the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' as <second_dispatch_type> response
    Then the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' should have been <second_dispatch_type> dispatched
    Examples:
      | first_dispatch_type | second_dispatch_type |
      | automatic           | requested            |
      | requested           | primary              |
      | other               | automatic            |
