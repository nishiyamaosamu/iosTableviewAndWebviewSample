////////////////////////////////////////////////////////////////////////////
//
// Copyright 2014 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <Realm/RLMCollection.h>
#import <Realm/RLMDefines.h>

RLM_ASSUME_NONNULL_BEGIN

@class RLMObject, RLMRealm, RLMResults RLM_GENERIC_COLLECTION;

/**

 RLMArray is the container type in Realm used to define to-many relationships.

 Unlike an NSArray, RLMArrays hold a single type, specified by the `objectClassName` property.
 This is referred to in these docs as the “type” of the array.

 When declaring an RLMArray property, the type must be marked as conforming to a
 protocol by the same name as the objects it should contain (see the
 `RLM_ARRAY_TYPE` macro). RLMArray properties can also use Objective-C generics
 if available. For example:

     RLM_ARRAY_TYPE(ObjectType)
     ...
     @property RLMArray<ObjectType *><ObjectType> *arrayOfObjectTypes;

 RLMArrays can be queried with the same predicates as RLMObject and RLMResults.

 RLMArrays cannot be created directly. RLMArray properties on RLMObjects are
 lazily created when accessed, or can be obtained by querying a Realm.
 */

@interface RLMArray RLM_GENERIC_COLLECTION : NSObject<RLMCollection, NSFastEnumeration>

/**---------------------------------------------------------------------------------------
 *  @name RLMArray Properties
 *  ---------------------------------------------------------------------------------------
 */

/**
 Number of objects in the array.
 */
@property (nonatomic, readonly, assign) NSUInteger count;

/**
 The class name (i.e. type) of the RLMObjects contained in this RLMArray.
 */
@property (nonatomic, readonly, copy) NSString *objectClassName;

/**
 The Realm in which this array is persisted. Returns nil for standalone arrays.
 */
@property (nonatomic, readonly, nullable) RLMRealm *realm;

/**
 Indicates if an array can no longer be accessed.
 */
@property (nonatomic, readonly, getter = isInvalidated) BOOL invalidated;

#pragma mark -

/**---------------------------------------------------------------------------------------
 *  @name Accessing Objects from an Array
 * ---------------------------------------------------------------------------------------
 */

/**
 Returns the object at the index specified.

 @param index   The index to look up.

 @return An RLMObject of the class contained by this RLMArray.
 */
- (RLMObjectType)objectAtIndex:(NSUInteger)index;

/**
 Returns the first object in the array.

 Returns `nil` if called on an empty RLMArray.

 @return An RLMObject of the class contained by this RLMArray.
 */
- (nullable RLMObjectType)firstObject;

/**
 Returns the last object in the array.

 Returns `nil` if called on an empty RLMArray.

 @return An RLMObject of the class contained by this RLMArray.
 */
- (nullable RLMObjectType)lastObject;


#pragma mark -


/**---------------------------------------------------------------------------------------
 *  @name Adding, Removing, and Replacing Objects in an Array
 *  ---------------------------------------------------------------------------------------
 */

/**
 Adds an object to the end of the array.

 @warning This method can only be called during a write transaction.

 @param object  An RLMObject of the class contained by this RLMArray.
 */
- (void)addObject:(RLMObjectArgument)object;

/**
 Adds an array of objects at the end of the array.

 @warning This method can only be called during a write transaction.

 @param objects     An enumerable object such as NSArray or RLMResults which contains objects of the
                    same class as this RLMArray.
 */
- (void)addObjects:(id<NSFastEnumeration>)objects;

/**
 Inserts an object at the given index.

 Throws an exception when called with an index greater than the number of objects in this RLMArray.

 @warning This method can only be called during a write transaction.

 @param anObject  An object (of the same type as returned from the objectClassName selector).
 @param index   The array index at which the object is inserted.
 */
- (void)insertObject:(RLMObjectArgument)anObject atIndex:(NSUInteger)index;

/**
 Removes an object at a given index.

 Throws an exception when called with an index greater than the number of objects in this RLMArray.

 @warning This method can only be called during a write transaction.

 @param index   The array index identifying the object to be removed.
 */
- (void)removeObjectAtIndex:(NSUInteger)index;

/**
 Removes the last object in an RLMArray.

 @warning This method can only be called during a write transaction.
*/
- (void)removeLastObject;

/**
 Removes all objects from an RLMArray.

 @warning This method can only be called during a write transaction.
 */
- (void)removeAllObjects;

/**
 Replaces an object at the given index with a new object.

 Throws an exception when called with an index greater than the number of objects in this RLMArray.

 @warning This method can only be called during a write transaction.

 @param index       The array index of the object to be replaced.
 @param anObject    An object (of the same type as returned from the objectClassName selector).
 */
- (void)replaceObjectAtIndex:(NSUInteger)index withObject:(RLMObjectArgument)anObject;

/**
 Moves the object at the given source index to the given destination index.

 Throws an exception when called with an index greater than or equal to the
 number of objects in this RLMArray.

 @warning This method can only be called during a write transaction.

 @param sourceIndex      The index of the object to be moved.
 @param destinationIndex The index to which the object at `sourceIndex` should be moved.
 */
- (void)moveObjectAtIndex:(NSUInteger)sourceIndex toIndex:(NSUInteger)destinationIndex;

/**
 Exchanges the objects in the array at given indexes.

 Throws an exception when either index exceeds the bounds of this RLMArray.

 @warning This method can only be called during a write transaction.

 @param index1 The index of the object with which to replace the object at index `index2`.
 @param index2 The index of the object with which to replace the object at index `index1`.
 */
- (void)exchangeObjectAtIndex:(NSUInteger)index1 withObjectAtIndex:(NSUInteger)index2;

#pragma mark -


/**---------------------------------------------------------------------------------------
 *  @name Querying an Array
 *  ---------------------------------------------------------------------------------------
 */
/**
 Gets the index of an object.

 Returns NSNotFound if the object is not found in this RLMArray.

 @param object  An object (of the same type as returned from the objectClassName selector).
 */
- (NSUInteger)indexOfObject:(RLMObjectArgument)object;

/**
 Gets the index of the first object matching the predicate.

 @param predicateFormat The predicate format string which can accept variable arguments.

 @return    Index of object or NSNotFound if the object is not found in this RLMArray.
 */
- (NSUInteger)indexOfObjectWhere:(NSString *)predicateFormat, ...;

/**
 Gets the index of the first object matching the predicate.

 @param predicate   The predicate to filter the objects.

 @return    Index of object or NSNotFound if the object is not found in this RLMArray.
 */
- (NSUInteger)indexOfObjectWithPredicate:(NSPredicate *)predicate;

/**
 Get objects matching the given predicate in the RLMArray.

 @param predicateFormat The predicate format string which can accept variable arguments.

 @return                An RLMResults of objects that match the given predicate
 */
- (RLMResults RLM_GENERIC_RETURN*)objectsWhere:(NSString *)predicateFormat, ...;

/**
 Get objects matching the given predicate in the RLMArray.

 @param predicate   The predicate to filter the objects.

 @return            An RLMResults of objects that match the given predicate
 */
- (RLMResults RLM_GENERIC_RETURN*)objectsWithPredicate:(NSPredicate *)predicate;

/**
 Get a sorted RLMResults from an RLMArray

 @param property    The property name to sort by.
 @param ascending   The direction to sort by.

 @return    An RLMResults sorted by the specified property.
 */
- (RLMResults RLM_GENERIC_RETURN*)sortedResultsUsingProperty:(NSString *)property ascending:(BOOL)ascending;

/**
 Get a sorted RLMResults from an RLMArray

 @param properties  An array of `RLMSortDescriptor`s to sort by.

 @return    An RLMResults sorted by the specified properties.
 */
- (RLMResults RLM_GENERIC_RETURN*)sortedResultsUsingDescriptors:(NSArray *)properties;

#pragma mark -

- (RLMObjectType)objectAtIndexedSubscript:(NSUInteger)index;
- (void)setObject:(RLMObjectType)newValue atIndexedSubscript:(NSUInteger)index;

#pragma mark -

/**---------------------------------------------------------------------------------------
 *  @name Unavailable Methods
 *  ---------------------------------------------------------------------------------------
 */

/**
 -[RLMArray init] is not available because RLMArrays cannot be created directly.
 RLMArray properties on RLMObjects are lazily created when accessed, or can be obtained by querying a Realm.
 */
- (instancetype)init __attribute__((unavailable("RLMArrays cannot be created directly")));

/**
 +[RLMArray new] is not available because RLMArrays cannot be created directly.
 RLMArray properties on RLMObjects are lazily created when accessed, or can be obtained by querying a Realm.
 */
+ (instancetype)new __attribute__((unavailable("RLMArrays cannot be created directly")));

@end

/**
 An RLMSortDescriptor stores a property name and a sort order for use with
 `sortedResultsUsingDescriptors:`. It is similar to NSSortDescriptor, but supports
 only the subset of functionality which can be efficiently run by the query
 engine. RLMSortDescriptor instances are immutable.
 */
@interface RLMSortDescriptor : NSObject

/**
 The name of the property which this sort descriptor orders results by.
 */
@property (nonatomic, readonly) NSString *property;

/**
 Whether this descriptor sorts in ascending or descending order.
 */
@property (nonatomic, readonly) BOOL ascending;

/**
 Returns a new sort descriptor for the given property name and order.
 */
+ (instancetype)sortDescriptorWithProperty:(NSString *)propertyName ascending:(BOOL)ascending;

/**
 Returns a copy of the receiver with the sort order reversed.
 */
- (instancetype)reversedSortDescriptor;

@end

@interface RLMArray (Swift)
// for use only in Swift class definitions
- (instancetype)initWithObjectClassName:(NSString *)objectClassName;
@end

RLM_ASSUME_NONNULL_END
