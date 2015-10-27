#language: en

Feature: Incident Dispatching
  In order to have a fire department respond to an incident
  I have to be able to dispatch the fire department

  Scenario Outline: Dispatching a fire department
    Given I have an incident '99e51168-950b-41b5-a346-f875d42af5f5'
    When I dispatch the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' as <dispatch_type> response at '<alarm_time>'
    Then the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' should have been <dispatch_type> dispatched at '<alarm_time>'
    Examples:
      | dispatch_type | alarm_time              |
      | primary       | 2005-01-23 02:59:12.000 |
      | automatic     | 2002-07-20 23:44:59.000 |
      | requested     | 2010-12-20 23:59:59.000 |
      | other         | 2002-01-20 19:46:59.000 |


  Scenario Outline: Correcting the dispatch
    Given I have an incident '99e51168-950b-41b5-a346-f875d42af5f5'
    When I dispatch the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' as <first_dispatch_type> response at '<alarm_time>'
    And I dispatch the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' as <second_dispatch_type> response at '<alarm_time>'
    Then the fire department 'c86517ea-4669-414e-9ce4-7ad35710ad0e' should have been <second_dispatch_type> dispatched at '<alarm_time>'
    Examples:
      | first_dispatch_type | second_dispatch_type | alarm_time              |
      | automatic           | requested            | 2002-01-20 23:59:59.000 |
      | requested           | primary              | 2003-01-19 20:59:59.000 |
      | other               | automatic            | 2006-12-20 23:57:54.000 |
